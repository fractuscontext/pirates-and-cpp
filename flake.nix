# SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
# SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
#
# SPDX-License-Identifier: MIT

{
  description = "Modern C++ Env: nix-darwin + VSCodium + VS2022 compatibility";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    git-hooks = {
      url = "github:cachix/git-hooks.nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = { self, nixpkgs, flake-utils, git-hooks }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };

        pre-commit-check = git-hooks.lib.${system}.run {
          src = ./.;
          hooks = {
            nixpkgs-fmt.enable = true;

            markdownlint = {
              enable = true;
              name = "Markdown Lint Check";
              entry = "${pkgs.markdownlint-cli}/bin/markdownlint .";
              pass_filenames = false;
            };

            doxygen-check = {
              enable = true;
              name = "Doxygen Documentation Check";
              entry = "${pkgs.doxygen}/bin/doxygen Doxyfile";
              pass_filenames = false;
              always_run = true;
            };

            reuse = {
              enable = true;
              name = "SPDX License Check";
              entry = "${pkgs.reuse}/bin/reuse lint";
              pass_filenames = false;
            };

            clang-format = {
              enable = true;
              types_or = [ "c" "c++" ];
            };

            clang-tidy = {
              enable = true;
              types_or = [ "c" "c++" ];
            };
          };
        };
      in
      {
        checks = { inherit pre-commit-check; };

        devShells.default = pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } {
          packages = with pkgs; [
            # C++ Toolchain
            cmake
            gtest
            lldb
            ninja
            clang-tools
            llvmPackages.llvm # llvm-cov, llvm-profdata for coverage

            # Hook Dependencies
            reuse
            markdownlint-cli
            nixpkgs-fmt
            doxygen
          ] ++ lib.optionals stdenv.isLinux [
            valgrind-light
          ];

          shellHook = ''
            ${pre-commit-check.shellHook}
            export CPATH="${pkgs.clang-tools}/resource"
          '';
        };
      });
}
