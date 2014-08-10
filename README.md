```

        ▄▀▀▀█▄    ▄▀▀█▄   ▄▀▀▄ ▀▄  ▄▀▀█▄   ▄▀▀▀█▀▀▄  ▄▀▀█▀▄    ▄▀▄▄▄▄  
       █  ▄▀  ▀▄ ▐ ▄▀ ▀▄ █  █ █ █ ▐ ▄▀ ▀▄ █    █  ▐ █   █  █  █ █    ▌ 
       ▐ █▄▄▄▄     █▄▄▄█ ▐  █  ▀█   █▄▄▄█ ▐   █     ▐   █  ▐  ▐ █      
        █    ▐    ▄▀   █   █   █   ▄▀   █    █          █       █      
        █        █   ▄▀  ▄▀   █   █   ▄▀   ▄▀        ▄▀▀▀▀▀▄   ▄▀▄▄▄▄▀ 
       █         ▐   ▐   █    ▐   ▐   ▐   █         █       █ █     ▐  
       ▐                 ▐                ▐         ▐       ▐ ▐        

            ~  FANED: The Fanatic client for Fanatic people  ~

```
##About

Fanatic Edition is an editing oriented [Sauerbraten](http://sauerbraten.org) client modification, developed by [Fanatic](http://fanaticclan.com) members and licensed under the [zlib/libpng](http://www.opensource.org/licenses/zlib-license.php) license.

##Features
- Ingame iRC client
- Blender Import/Export
- Client side cheat detection
- Ingame file sharing function
- Highly improved quickedit and editing menu
- Send your maps - if calced - inclusive lightmaps
- Ultra fast calclight using player's position and radius
- New and improved shot effects inclusive additional hudguns
- Implemented [Marching Cubes](http://www.youtube.com/watch?v=TstJlsEKEHs) by Wrack

... and much more!

##Screenshot

![screenshot](http://i.imgur.com/gl3vKBZ.jpg)

##Installation

- Step §1: Download the latest Sauerbraten SVN repository [here](http://svn.code.sf.net/p/sauerbraten/code).

- Step §2: Download the latest Fanatic Edition repository [here](https://github.com/incognito357/Sauer_FanaticEdition/archive/master.zip).

- Step §3: Unzip and copy everythig into your fresh created Sauerbraten SVN directory.

- Step §4: Run *sauer_faned.bat* (*sauer_faned.sh* on linux) to fire up the game.

##Compiling on Linux

- Step §1: Get the dependencies: `sudo apt-get install build-essential libsdl{,-mixer,-image}1.2-dev`.

- Step §2: Compile using gcc: `make -sC faned_src/ clean; make -sC faned_src/ install`.

- Step §3: If everything worked, run *sauer_faned.sh* to fire up the game.

##Informations

- The client side cheat detection is secure, but LAG may give you false positives; always do a manual check (spectating) after you got a detection warning to be 100% secure. Currently supported cheat detections: _CubeScript Injections_ inside map variables (if `/detect 1`, faned will re-print every map variable change escaped), _Edit mode in non coop edit game mode_ (if `/detect 1`, faned will print edittoggled/flying players), _Telekill_ (if `/detect 1`, faned will check if the actors position matches the victims position) and _Weapon Range Modifications_ (if `/detect 1`, faned will print if shots went beyond the range of the selected weapon).

- You can set for your rilfe shots up to 6 different particles. Currently supported: `/shotstyle` 1 for smoke, 2 for steam, 3 for spark, 4 for snow, 5 for laser and 6 for lightning. Don't forget while setting up your desired shotstyle to play with the settings for `/shotcolour`, `/shotduration`, `/shotgravity` and `/shotwidth` to match your chosen particle style. An example for a pink colored snow cannon would be: `/shotstyle 4; shotcolor 0xff0055; shotduration 2000; shotwidth 1`. Another example for a red colored laser cannon: `/shotstyle 5; shotcolor 0xff0000; shotduration 3000; shotwidth 1`. If you don't like sparks, disable them via `/shotsparks 0` and if you don't want any shot style at all, simply disable everything via `/shotstyle 0` and gain some more fps in return.

- To use the blender importer, first install Wrack's python exporter addon (faned/smc/io_export_smc.py) into Blender: *File > User Preferences > Addons > Install Addon* and don't forget to activate it. Now create some geometry, hit *File > Export > Sauerbraten (.smc)* and back at sauerbraten, simply enter `/importsmc PATH/FiLE.smc`. This will load the .smc (Sauerbraten Marching Cubes) file to your current selection. Note that you can set grid and cube counts while exporting; try to find the golden ratio to get sane results. 

##Commands

- `autorespawn 0|1` Self-explaining
- `backgroundimage PATH/FiLE.png` Self-explaining
- `backgroundlogo PATH/FiLE.png` Self-explaining
- `bloodcolour RGB|HEX` Change the color of blood squirts
- `bloodintensity FLOAT` Change how much blood is squirted
- `buildcylinder RADiUS HEiGHT POWER POSiTiON-X POSiTiON-Y POSiTiON-Z)` Self-explaining
- `buildhelix RADiUS HEiGHT POWER)` Self-explaining
- `buildoctahedron RADiUS POWER POSiTiON-X POSiTiON-Y POSiTiON-Z)` Self-explaining
- `buildparaboloid RADiUS POWER POSiTiON-X POSiTiON-Y POSiTiON-Z)` Self-explaining
- `buildsphere RADiUS POWER POSiTiON-X POSiTiON-Y POSiTiON-Z SHAPE-X SHAPE-Y SHAPE-Z)` Self-explaining
- `buildtorus RADiUS RANGE DiRECTION POSiTiON-X POSiTiON-Y POSiTiON-Z)` Self-explaining
- `calclightradius RADiUS` Local calclight at player's current position with given radius; set to 0 to disable)
- `clearbots` Remove all connected bots
- `clearpickups` Remove all ffa ents: ammo, health, armor, etc.
- `consmoothfade 0|1` Enable or disable smooth console fading
- `contimestamp 0|1` Enable or disable console time.
- `crosshaircolor RGB|HEX` Change the color of your crosshair
- `deathpanicsound 0|1` Enable or disable the deathpanic heartbeat sound
- `deathpanicscreen 0|1` Enable or disable the deathpanic eyeveins screen
- `detect 0|1` Enable or disable the client side cheat detection
- `editent iNDEX X Y Z TYPE ATTR1 ATTR2 ATTR3 ATTR4 ATTR5` Create a new entity at a position with attributes
- `editmute CN` / `uneditmute CN` Self-explaining
- `execdir DiRECTORY` Executes all .cfg files in the given directory
- `getversion` Self-explaining
- `getversionfull` Self-explaining
- `getvalpha TEXTURE-iD` Return the valpha of the given texture
- `getvcolor TEXTURE-iD` Return the vcolor of the given texture
- `getvlayer TEXTURE-iD` Return the vlayer of the given texture
- `getvoffset TEXTURE-iD` Return the x and y voffset of the given texture
- `getvrotate TEXTURE-iD` Return the vrotation state of the given texture
- `getvscale TEXTURE-iD` Return the vscale state of the given texture
- `getvscroll TEXTURE-iD` Return the x and y vscroll state of the given texture
- `grid2Dselectioncolor RGB|HEX` Set the color of the 2D selection box in editmode
- `grid3Dselectioncolor RGB|HEX` Set the color of the 3D selection box in editmode
- `gridhoverselectioncolor RGB|HEX` Set the color of the hovered selection in editmode
- `gridselectioncolor RGB|HEX` Set the color of the selection in editmode
- `hideversion 0|1` Enable or disable Fanatic Edition's version in main menu
- `importsmc FiLE` Import .smc files exported from Blender
- `ircaddchan iRCNET CHAN` Add a channel to the network
- `ircaddclient iRCNET HOST PORT NiCK` Set up your client
- `ircaddrelay` Relay everything but verbose messages
- `ircauth AUTHNAME AUTHPASS` Self-explaining
- `ircbind iRCNET ADDRESS` Bind to a specific address
- `ircconnect iRCNET` Connect client to network
- `ircconns` Return iNT of current connections
- `ircdisconnect` Self-explaining
- `ircfilter 0|1|2` Defines the way the colour-to-irc filter works; 0 = off, 1 = convert, 2 = strip
- `ircfriendlychan iRCNET CHAN NAME` Set another friendly name for the relay on this channel
- `ircjoinchan iRCNET CHAN` Self-explaining
- `ircnick iRCNET NiCK` Self-explaining
- `ircpass iRCNET PASS` Self-explaining
- `ircpasschan iRCNET CHAN PASS` Self-explaining
- `ircport iRCNET PORT` Set the port to the network
- `ircquitmsg "MESSAGE"` Sends "MESSAGE" as quit message when disconnecting via /ircdisconnect
- `ircrelaychan iRCNET CHAN RELAY` Self-explaining
- `ircserv iRCNET SERVER` Set the server to the network
- `nearmiss 0|1` Enable or disable near-missed shot sounds
- `sayirc iRCNET CHAN TEXT` Sends the message TEXT to irc
- `outlinecolour RGB|HEX` Set the color of the outline
- `outline 0|1` Enable or disable outline mode
- `pickupautoswitch 0|1` Enable or disable automatic weapon change on ammo pickup
- `receiveai 0|1` Self-explaining
- `receivenewmap 0|1` Self-explaining
- `receiveremip 0|1` Self-explaining
- `receivesendmap 0|1` Self-explaining
- `savebak 0|1|2|3` backup saving; 0: `no backup`, 1: `mapname.BAK`, 2: `mapname_totalmillis.BAK`, 3: `mapname_date_time.BAK`
- `savemapshot 0|1` Enable or disable saving a preview mapshot when saving the map
- `sehud 0|1` Enable or disable the SauerEnhanced HUD
- `selectionguard 0|1` Enable or disable a warning about editing a selection that is not in view
- `shotcolour RGB|HEX` Set custom weapons smoke colors
- `shotcolourrainbow 0|1` Set custom weapons smoke colors randomly colored
- `shotduration FLOAT` Set custom shotduration of smoke (rifle)
- `shotgravity FLOAT` Set custom shotgravity of smoke (rifle)
- `shotwidth FLOAT` Set custom shotwidth of smoke (rifle)
- `shotsparks 0|1` Enable or disable shotsparks (chaingun, pistol, rifle)
- `shotstyle 0|1|2|3|4|5|6` Set custom shotstyle (rifle: 1: smoke, 2: steam, 3: spark, 4: snow, 5: laser, 6: lightning)
- `showtimeremaining 0|1` Show remaining time at upper right corner/below minimap
- `specall 0|1` Spectate all connected clients (1 spectates yourself as well)
- `spec CN` Shortcut for `/spectator CN 1`, spectate a client
- `telecn CN X Y Z` Teleport player from his current position to another
- `unspecall 0|1` Unspectate all connected clients (1 spectates yourself as well)
- `unspec CN` Shortcut for `/spectator CN 0` unspectate a client
- `wireframe 0|1` Enable or disable wireframe mode
- `zoomscopescreen 0|1` Enable or disable the zoom scope screen (rifle)

##Credits

- **bum**: coding, scripting

- **Nyne**: coding, scripting, stealing

- **Q009**: allowing to steal from SauerEnhanced

- **Wrack**: allowing to steal from Marching Cubes

- **Mist**: bug reporting, beta testing, brainstorming
