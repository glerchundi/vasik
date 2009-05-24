print 'b';
require('glwindow');
print 'c';
require('soundsystem');
require('effect');
require('scheduler');
require('imagesystem');

-- CREATE OBJECTS
window   = glwindow:glwindow();
soundsys = soundsystem:soundsystem();
schdlr   = scheduler:scheduler();
fx       = effect:effect();
imgsys   = imagesystem:imagesystem();

-- INIT WINDOW
window:init('iNguma',640,480,32,false);

-- INIT SOUNDSYSTEM
soundsys:init();
soundsys:spectrum(true);
soundsys:detection_threshold(1);
soundsys:detection_method(soundsystem.DETECTBEAT_UNIFORM);
soundsys:loadstream("oasis"    ,"data/Oasis - Wonderwall.mp3"            );
soundsys:loadstream("ministry" ,"data/Ministry of Sound - Every Word.mp3");
soundsys:loadstream("coldplay" ,"data/Coldplay - Violet Hill.mp3"        );
soundsys:loadstream("anestesia","data/Anestesia - Terrorista.mp3"        );
soundsys:playstream("coldplay");
--soundsys:test02();

-- INIT IMAGESYSTEM
imgsys:init();
imgsys:create("perlin01",256,256,32);
imgsys:perlin("perlin01",0.125,0.60,8);
--imgsys:load("perlin02","perlin01.png");
imgsys:save("perlin01");

-- INIT IMAGESYSTEM
imgsys:init();
imgsys:create("perlin01",256,256,32);
imgsys:perlin("perlin01",0.125,0.60,8);
--imgsys:load("perlin02","perlin01.png");
imgsys:save("perlin01");

-- INIT EFFECTS
fx:init();

-- INIT SCHEDULER
schdlr:init();

while window:isfinished() == false do
    window:eventhandler();    

	fx:render(soundsys:getspectrum());
	soundsys:detectbeat("ministry");

    window:swapbuffers();
end


schdlr:quit();
fx:quit();
imgsys:quit();
soundsys:quit();
window:quit();
