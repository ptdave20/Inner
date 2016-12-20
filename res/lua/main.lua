--
-- Created by IntelliJ IDEA.
-- User: ptdave
-- Date: 12/16/16
-- Time: 2:24 PM
--

window = Window.new()
bgMusic = MusicResource.new("music/Giant Wyrm.ogg")
bgMusic:play()
bgMusic:setLoop(true)
if window:openConfig("json/main.json") then
    window:createWindow()


    window:run()
end