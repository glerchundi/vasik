require('demosystem');

-- CREATE OBJECTS
window      = demosystem.window();
soundsys    = demosystem.soundsystem();
fxcubes     = demosystem.effect();
scheduler   = demosystem.scheduler();
timer       = demosystem.timer();
font        = demosystem.font();

-- INIT WINDOW
window:init('Vasik*',640,480,32,false);

-- INIT SOUNDSYSTEM
soundsys:init();
soundsys:spectrum(true);
soundsys:loadstream("oasis","data/Oasis - Wonderwall.mp3");
soundsys:playstream("oasis");

-- INIT TIMER
timer:init();

-- INIT FONT
font:init();
font:setFont("data/Andale Mono.ttf",12);

-- INIT EFFECTS
fxcubes:init();
fxcubes:initplugin("window", window);
fxcubes:initplugin("timer", timer);
fxcubes:initplugin("font", font);

-- INIT SCHEDULER
scheduler:init(1);
scheduler:initplugin("window", window);
scheduler:initplugin("timer", timer);
scheduler:initplugin("cubes", fxcubes);

scheduler:addfx(0,0,-1,"cubes","render", nil);

scheduler:play(0);

scheduler:quit();
fxcubes:quit();
soundsys:quit();
window:quit();
