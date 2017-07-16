#include "CustomRenderTexture.h"


USING_NS_CC;

CustomRenderTexture * CustomRenderTexture::create(int w, int h, Texture2D::PixelFormat eFormat)
{
    CustomRenderTexture *ret = new (std::nothrow) CustomRenderTexture();

    if(ret && ret->initWithWidthAndHeight(w, h, eFormat))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

CustomRenderTexture * CustomRenderTexture::create(int w ,int h, Texture2D::PixelFormat eFormat, GLuint uDepthStencilFormat)
{
    CustomRenderTexture *ret = new (std::nothrow) CustomRenderTexture();

    if(ret && ret->initWithWidthAndHeight(w, h, eFormat, uDepthStencilFormat))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

CustomRenderTexture * CustomRenderTexture::create(int w, int h)
{
    CustomRenderTexture *ret = new (std::nothrow) CustomRenderTexture();

    if(ret && ret->initWithWidthAndHeight(w, h, Texture2D::PixelFormat::RGBA8888, 0))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void CustomRenderTexture::begin()
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when setting matrix stack");
    
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    _projectionMatrix = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    _transformMatrix = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    if(!_keepMatrix)
    {
        director->setProjection(director->getProjection());
        
        const Size& texSize = _texture->getContentSizeInPixels();
        
        // Calculate the adjustment ratios based on the old and new projections
        Size size = director->getWinSizeInPixels();
        
        float widthRatio = size.width / texSize.width;
        float heightRatio = size.height / texSize.height;
        
        Mat4 orthoMatrix;
        Mat4::createOrthographicOffCenter((float)-1.0 / widthRatio, (float)1.0 / widthRatio, (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1, 1, &orthoMatrix);
        director->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, orthoMatrix);
    }

    //_groupCommand.init(_globalZOrder);

    /*Renderer *renderer =  Director::getInstance()->getRenderer();
    renderer->addCommand(&_groupCommand);
    renderer->pushGroup(_groupCommand.getRenderQueueID());*/

    _beginCommand.init(_globalZOrder);
    _beginCommand.func = CC_CALLBACK_0(CustomRenderTexture::onBegin, this);

    Director::getInstance()->getRenderer()->addCommand(&_beginCommand);
}

void CustomRenderTexture::end()
{
    _endCommand.init(_globalZOrder);
    _endCommand.func = CC_CALLBACK_0(CustomRenderTexture::onEnd, this);

    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when setting matrix stack");
    
    Renderer *renderer = director->getRenderer();
    renderer->addCommand(&_endCommand);
    //renderer->popGroup();
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

}
