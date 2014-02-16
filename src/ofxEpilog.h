/*
 
 ofxEpilog - OpenFrameworks library for Epilog laser cutter.
 
 
 Copyright (C) 2002-2008 Andrews & Arnold Ltd <info@aaisp.net.uk>
 Copyright (C) 2008 AS220 Labs <brandon@as220.org>
 Copyright (C) 2011 Trammell Hudson <hudson@osresearch.net>
 Copyright (C) 2013 Mitsuhito Ando <mitsuhito.ando@gmail.com>
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef epilogTest_ofxEpilog_h
#define epilogTest_ofxEpilog_h

#include "ofMain.h"
#include "ofxNetwork.h"

#define MM_PER_INCH 25.4

enum JOB_TYPE {VECTOR, RASTER};
//enum MODEL {FUSION, MINI, HELIX, UNKNOWN};

typedef struct LaserCutterOutputConfig
{
    unsigned short vspeed;
    unsigned short vpower;
    unsigned short rspeed;
    unsigned short rpower;
    enum RASTER_MODE { BMP16M = 7, BMPGRAY = 2 };
    RASTER_MODE rasterMode;
    unsigned short dpi;
    unsigned short freq;
    bool autoFocusEnabled;
} OutputConfig;

typedef struct LaserCutterWorkareaSize
{
    unsigned int width;
    unsigned int height;
    unsigned int z;
} WorkareaSize;

//
// HPGLBuffer creates HPGL formatted string from ofPath, ofPolyline, ofPixels, ofImage, pdf, eps, jpg, png, gif ...
// If you want to create from other types, make sub class and overload static method.
//
class HPGLBuffer : public ofBuffer
{
public:
    HPGLBuffer() : ofBuffer()
    {
        //ofLog(OF_LOG_VERBOSE, "HPGLBuffer() is called." + ofToString(this));
    };
    
    virtual ~HPGLBuffer()
    {
        //ofLog(OF_LOG_VERBOSE, "~HPGLBuffer() is called." + ofToString(this));
    };
    
    static ofPtr<HPGLBuffer> create(ofPolyline line, OutputConfig config);
    static ofPtr<HPGLBuffer> create(ofPath path, OutputConfig config);
    static ofPtr<HPGLBuffer> create(ofImage img, ofPoint offset, OutputConfig config); // offset(mm)
    static ofPtr<HPGLBuffer> create(ofPixels pixelsRef, ofPoint offset, OutputConfig config); // offset(mm)
    static ofPtr<HPGLBuffer> createFromPaylaodFile(const string path, const string delimiter, ofPoint offset, OutputConfig config); // For debug
};

//
// GMLBuffer creates HPGL formatted string from Graffiti Markup Language.
// To know GML detail, see http://www.graffitimarkuplanguage.com/g-m-l-spec/ .
//
class GMLBuffer : public HPGLBuffer
{
public:
    GMLBuffer() : HPGLBuffer()
    {
        //ofLog(OF_LOG_VERBOSE, "GMLBuffer() is called." + ofToString(this));
    };
    
    virtual ~GMLBuffer()
    {
        //ofLog(OF_LOG_VERBOSE, "~GMLBuffer() is called." + ofToString(this));
    };
    static ofPtr<GMLBuffer> create(string gmlFilePath, OutputConfig config);
};

//class ofxEpilog : public ofThread
class ofxEpilog
{
public:
    ofxEpilog();
    ofxEpilog(const ofxEpilog &obj);
    ofxEpilog(string ip);
    ofxEpilog(string ip, WorkareaSize size);
    ofxEpilog(string ip, WorkareaSize size, OutputConfig config);
    ~ofxEpilog();
    
    bool connect(string ip, bool liveMode=false);
    void disconnect();
    bool isConnected();
    
    void setWorkareaSize(WorkareaSize size);
    WorkareaSize getWorkareaSize();
    
    void setIPAddress(string ip);
    string getIPAddress() { return ipAddr; };
    
    void setOutputConfig(OutputConfig config);
    OutputConfig getOutputConfig();

    bool send(const ofPtr<HPGLBuffer> &buffer, JOB_TYPE type);    

protected:
    string ipAddr;
    WorkareaSize workareaSize;
    OutputConfig outputConfig;
    ofxTCPClient tcpClient;
    static const uint PRINTER_SERVICE_PORT = 515;
    //MODEL modelType;
    bool isLiveMode;
    unsigned long sentCount;
    //void threadedFunction();
    
    string hostname;
    
    bool sendVectorJobHeader();
    bool sendVectorJobFooter();
    
    bool sendPJLHeader();
    bool sendPJLFooter();
    
    bool sendPCLRasterHeader();
    bool sendPCLRasterJob(const ofPtr<HPGLBuffer> &buffer);
    bool sendPCLRasterFooter();
    
    bool sendPCLVectorHeader();
    bool sendPCLVectorJob(const ofPtr<HPGLBuffer> &buffer);
    bool sendPCLVectorFooter();
    
    bool updateVectorOutputConfig();
};

#endif
