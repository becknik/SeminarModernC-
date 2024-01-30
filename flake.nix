{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let pkgs = nixpkgs.legacyPackages.${system};
      in {
        devShell = pkgs.mkShell {
          shellHook = '''';
          buildInputs = with pkgs; [
            bashInteractive

            (texliveMedium.withPackages (ps: with ps; [
              mmap
              csquotes
              hyphenat
              pgfplots
              biblatex
            ]))

            clang_17
            gcc13

            cmake
            ninja

            curlFull
            nlohmann_json
          ];
        };
      });
}