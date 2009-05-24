require('glwindow');
require('soundsystem');
require('effect');
require('imagesystem');

-- CREATE OBJECTS
window   = glwindow:glwindow();
soundsys = soundsystem:soundsystem();
fx       = effect:effect();
imgsys   = imagesystem:imagesystem();

-- INIT WINDOW
window:init('iNguma',640,480,32,false);

-- INIT SOUNDSYSTEM
soundsys:init();
soundsys:spectrum(true);
soundsys:loadstream("oasis"    ,"data/Oasis - Wonderwall.mp3"            );
soundsys:loadstream("coldplay" ,"data/Coldplay - Violet Hill.mp3"        );
soundsys:playstream("oasis");

-- INIT IMAGESYSTEM
imgsys:init();
--imgsys:load("perlin02","perlin01.png");

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