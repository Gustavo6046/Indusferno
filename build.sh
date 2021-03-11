function cc {
    gdcc-cc -c -o build/"$1".ir src/"$1".c
}

function ld {
    gdcc-ld build/*.ir -o build/"$1".o
}

cc error
cc industry
cc stations
cc def_cargo
cc def_indus
ld infindus
