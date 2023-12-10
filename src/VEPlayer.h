#ifndef __VEPLAYER__
#define __VEPLAYER__

#include<string>

class VEPlayer{
    public:
    VEPlayer();
    ~VEPlayer();

    ///setDataSource
    int setDataSource(std::string path);

    ///prepare
    int prepare();

    ///start
    int start();

    ///stop
    int stop();

    ///pause
    int pause();

    ///resume
    int resume();

    ///release
    int release();

    ///reset
    int reset();

    ///setLooping

    ///isLooping

    ///getCurrentPosition

    ///getDuration

    ///setDisplay

    ///setVolume

    ///getTrackInfo

    ///setPlaybackParams

    ///setOnCompletionListener

    ///setOnErrorListener

    ///setOnSeekCompleteListener

    private:

};

#endif