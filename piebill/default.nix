{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  name = "piebill";

  src = ./.;

  nativeBuildInputs = with pkgs; [
    cmake
    sfml
    pkg-config
    SDL2
    SDL2_gfx
    SDL2_ttf
    SDL2_image
  ];
}

