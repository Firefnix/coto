{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    nativeBuildInputs = with pkgs.buildPackages; [
      gcc_multi
      cmake
    ];
  shellHook = ''
    alias prebuild="cmake -S . -B build -DCMAKE_BUILD_TYPE=Release";
    alias build="cmake --build build";
  '';
}

