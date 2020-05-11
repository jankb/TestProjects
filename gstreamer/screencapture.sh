GST_DEBUG=2 gst-launch-1.0 -vvv \
ximagesrc use-damage=0 num-buffers=1000 endx=680 endy=500 ! \
'video/x-raw, framerate=25/1' ! \
videoscale ! \
'video/x-raw, width=640, height=480' ! \
glimagesink sync=false
#aasink driver=curses

