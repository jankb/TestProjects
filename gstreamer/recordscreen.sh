GST_DEBUG=3 gst-launch-1.0 -vvv \
ximagesrc num-buffers=250 endx=640 endy=480 ! \
'video/x-raw(ANY), format=I420, width=640, height=480, framerate=1/25' ! \
videoscale ! \
'video/x-raw, width=640, height=480' ! \
videoconvert ! \
omxh264enc ! \
'video/x-h264, width=640, height=480'  ! \
filesink location=screenrec.avi 
#glimagesink sync=false
#
#gst-launch-1.0 -vv \
#ximagesrc num-buffers=200 ! \
#'video/x-raw' ! \
#omxh264enc ! \
#'video/x-h264'  ! \
#filesink location=screenrec.avi 
