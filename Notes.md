## GStreamer

### Add VLan
```
ip link add link eth0 name vlan12 type vlan id 12
ip route add <multicastaddr>/16 dev vlan12
ip address add <ipaddr>/24 dev vlan12
```
### Create video using GStreamer
```
gst-launch-1.0 videotestsrc num-buffers=200 ! 'video/x-raw, width=800, height=600' ! jpegenc ! avimux ! filesink location=smpte.avi
```
### Stream video to multicast using VLC
```
cvlc -v smpte.avi --loop --sout '#transcode{vcodec=h264, venc=x264{options={repeat-headers=1},level=4,profile=baseline,keyint=1},scale=Auto,acodec=none}:rtp{dst=239.192.1.1,port=5005}'
```

### Receive video using GStreamer
```
gst-launch-1.0 -vvv udpsrc address=239.192.1.1 port=5005 ! queue ! 'application/x-rtp, encoding-name=H264, width=800, height=600, framerate=30' ! rtph264depay ! 'video/x-h264, width=800, height=600, framerate=30' ! h264parse ! 'video/x-h264, stream-format=byte-stream' ! omxh264dec ! queue ! glimagesink sync=false
```

### Send and receive h264
Test video (ball)
```
#!/bin/bash
DISPLAY=:0 GST_DEBUG=2 gst-launch-1.0 -vvv videotestsrc pattern=ball ! \
'video/x-raw, width='$1', height='$2', framerate='$3'/1' ! \
nvvidconv ! \
'video/x-raw(memory:NVMM), width='$1', height='$2', format=(string)I420, framerate='$3'/1' ! \
omxh264enc profile=1 iframeinterval=1 control-rate=2 bitrate=3000000 ! \
'video/x-h264, width='$1', height='$2', stream-format=(string)byte-stream, framerate='$3'/1' ! \
rtph264pay ! \
udpsink host=192.168.1.70 sync=false
```

Grab screen/application window using ximagesrc
```
#!/bin/bash
#DISPLAY=:0 GST_DEBUG=2 gst-launch-1.0 -vvv ximagesrc use-damage=0 endx=$1 endy=$2 ! \
DISPLAY=:0 GST_DEBUG=2 gst-launch-1.0 -vvv ximagesrc use-damage=0 xname='xclock' ! \
'video/x-raw, framerate='$3'/1' ! \
nvvidconv ! \
'video/x-raw(memory:NVMM), width='$1', height='$2', format=(string)I420, framerate='$3'/1' ! \
omxh264enc profile=1 iframeinterval=1 control-rate=2 bitrate=3000000 ! \
'video/x-h264, width='$1', height='$2', stream-format=(string)byte-stream, framerate='$3'/1' ! \
rtph264pay ! \
udpsink host=192.168.1.70 sync=false
```

Show video
```
GST_DEBUG=2 gst-launch-1.0 -vvv udpsrc=192.168.1.70 port=5004 caps="application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264, patacetization-mode=(string)1, payload=(int)96" ! \
rtph264depay ! \
'video/x-h264, alignment=(string)au, profile=(string)baseline, level=(string)4, stream-format=(string)byte-stream' ! \
h264parse ! \
omxh264dec ! \
nveglglessink window-width=640 window-height=480
```

## Programming
### Serialization
```C++
 
 template <typename T>
 void serialize(T data)
 { 
   std::cout << data << std::endl;
 }

 template <>
 void serialize(int* data)
 { 
   std::cout << *data << std::endl;
}
 
 template <class C>
 void serialize(std::vector<typename C::value_type> data)
 {
   std::cout << "std::vector - begin"<<std::endl;
   for (std::vector<C::value_type>::const_iterator cit = data.begin(); cit != data.end(); cit++)
   {
     serialize<C::value_type>(*cit);
   }
   std::cout << "std::vector - end"<<std::endl;
 }

 template <class C>
 void serialize(std::map<typename C::key_type, typename C::mapped_type> data)
 {
   std::cout << "std::map - begin"<<std::endl;
   for (std::map<C::key_type,C::mapped_type>::const_iterator cit = data.begin(); cit != data.end(); cit++)
   {
     serialize<C::key_type>(cit->first);
     serialize<C::mapped_type>(cit->second);
   }
   std::cout << "std::map - end"<<std::endl;
 }
 ```
