{ pkgs ? import <nixpkgs>{} }:

pkgs.stdenv.mkDerivation {
  name = "connect4";
  src = ./.;

  buildInputs = with pkgs; [
    cmake
  ];

}

