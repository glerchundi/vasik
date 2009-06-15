require('demosystem');

-- CREATE OBJECTS
window      = demosystem.window();
soundsys    = demosystem.soundsystem();
fxcubes     = demosystem.effect();
scheduler   = demosystem.scheduler();
timer       = demosystem.timer();
font        = demosystem.font();
shell       = demosystem.shell();

-- INIT WINDOW
window:init('Vasik*',640,480,32,false);

-- INIT SOUNDSYSTEM
soundsys:init();
soundsys:loadstream("oasis","data/Oasis - Wonderwall.mp3");
--soundsys:playstream("oasis");

-- INIT TIMER
timer:init();

-- INIT FONT
font:initplugin("window", window);
font:init();
font:setFont("data/Fixedsys500c.ttf",10);

-- INIT SHELL
shell:initplugin("window", window);
shell:initplugin("timer", timer);
shell:initplugin("font", font);
shell:init();

-- INIT EFFECTS
fxcubes:initplugin("window", window);
fxcubes:initplugin("timer", timer);
fxcubes:initplugin("font", font);
fxcubes:init();

-- INIT SCHEDULER
scheduler:initplugin("window", window);
scheduler:initplugin("timer", timer);
scheduler:initplugin("cubes", fxcubes);
scheduler:initplugin("shell", shell);
scheduler:init(1);

scheduler:addfx(0,0,-1,"cubes","render", nil);
scheduler:addfx(0,0,-1,"shell","render",nil);

scheduler:play(0);

shell:quit();
font:quit();
timer:quit();
scheduler:quit();
fxcubes:quit();
soundsys:quit();
window:quit();
