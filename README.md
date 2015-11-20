Trying to wrap my head around implementing state machines in an SDL2 game prototype


Status (May be outdated, I'm lazyAF):

fills background with tiles depending on state

stamps a sand tile in the top left to test I can

'e' key moves from "cutscene" state to "overworld" then swaps between "overworld and "underworld"

'm' key toggles "menu" state

ESC quits only when in menu state, otherwise close via window manager (x button or whatever you got to close windos)

Command line flags: -d `<display_number>` -s `<tile_size>`
