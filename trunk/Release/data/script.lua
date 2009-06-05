require('glwindow');
require('soundsystem');
require('effect');
require('imagesystem');

-- CREATE OBJECTS
window   = glwindow.glwindow();
soundsys = soundsystem.soundsystem();
fx       = effect.effect();
imgsys   = imagesystem.imagesystem();

-- INIT WINDOW
window:init('Vasik*',640,480,32,false);

-- INIT SOUNDSYSTEM
soundsys:init();
soundsys:spectrum(true);
soundsys:loadstream("oasis"    ,"data/Oasis - Wonderwall.mp3"            );
soundsys:loadstream("coldplay" ,"data/Coldplay - Violet Hill.mp3"        );
soundsys:playstream("oasis");

-- INIT IMAGESYSTEM
imgsys:init();
imgsys:create("perlin01",256,256,32);
imgsys:perlin("perlin01",2,0.5,4);
imgsys:save("perlin01");

-- INIT EFFECTS
fx:init();

while window:isfinished() == false do
    window:eventhandler();    
    
    fx:render(soundsys:getspectrum());

    window:swapbuffers();
end

fx:quit();
imgsys:quit();
soundsys:quit();
window:quit();
