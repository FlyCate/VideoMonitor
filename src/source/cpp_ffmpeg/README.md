#cpp_ffmpeg
网上看了一些大牛的例子，怎么说呢？ 一坨坨的代码直接摞到main函数中，真是让人看起来蛋疼。 又看了JUVRTMPClient 这种漂亮的封装，就想做点事情，给FFMPEG做一个C++封装类。


定义 CFFMpeg 封装ffmpeg的初始化，打开流等操作。它包含

OpenInput 打开流

FindAV 查找Audio和Video流并获取相应的解码器

Process 开始处理流

CloseInput关闭流



目前这个类不支持Publish一个流。上面的设计时为播放流服务。



定义一个PacketListener接口，这个接口中的方法会在适当的时机被CFFMpeg调用

onRecvPacket 收到一个packet（没有解码）

onVideoFrame 解码得到一个视频帧

onAudioFrame 解码得到一个音频帧

onVideoSize 根据视频解码器得到一些大小、格式之类的信息。

onAudioParam 根据音频解码得到一些音频帧的特性（暂未实现）



使用方法： 创建一个PacketListener的派生类，在这个类中写你要做的事。

例子中PacketListener的派生类就是MyListener