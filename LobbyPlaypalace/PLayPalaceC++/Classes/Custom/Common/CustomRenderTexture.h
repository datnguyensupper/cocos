#pragma once
#include "cocos2d.h"

class CustomRenderTexture : public cocos2d::RenderTexture
{
public:
    /** Initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats are valid ) and depthStencil format. 
     *
     * @param w The RenderTexture object width.
     * @param h The RenderTexture object height.
     * @param format In Points and a pixel format( only RGB and RGBA formats are valid ).
     * @param depthStencilFormat The depthStencil format.
     */
    static CustomRenderTexture * create(int w ,int h, cocos2d::Texture2D::PixelFormat format, GLuint depthStencilFormat);

    /** Creates a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid. 
     *
     * @param w The RenderTexture object width.
     * @param h The RenderTexture object height.
     * @param format In Points and a pixel format( only RGB and RGBA formats are valid ).
     */
    static CustomRenderTexture * create(int w, int h, cocos2d::Texture2D::PixelFormat format);

    /** Creates a RenderTexture object with width and height in Points, pixel format is RGBA8888. 
     *
     * @param w The RenderTexture object width.
     * @param h The RenderTexture object height.
     */
    static CustomRenderTexture * create(int w, int h);

    /** Starts grabbing. */
    virtual void begin();

    /** Ends grabbing.
     * @lua endToLua
     */
    virtual void end();

    /** Clears the texture with a color. 
     *
     * @param r Red.
     * @param g Green.
     * @param b Blue.
     * @param a Alpha.
     */
};