大清早就来抄 tutorial (thanks to twinklebear's lessons)

为了看起来舒服，我把大部分判断异常的代码都删掉了，无非就是检查一下指针是否为 Null，自己加上去就行



## 配置

配置阶段遇到问题

`ld.exe: skipping incompatible lib/libSDLmain.a when searching for -lSDLmain`

解决：务必下载支持 64bit 的版本

我们这里用的是 SDL2，不能随便抄 SDL1 的代码，区别还是蛮大的



## Lesson 1: Hello World

显示一张图片（因为用的是 texture，图片会被自动拉伸）



## Lesson 2: 封装图片显示

如何显示一张图片？

``` 
loadTexture -> (SDL_QueryTexture) -> renderTexture -> (SDL_RenderPresent)
```

``` cpp
SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *ren)
{
    SDL_Texture *texture = nullptr;
    //Load the image
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
    //If the loading went ok, convert to texture and return the texture
    if (loadedImage != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        SDL_FreeSurface(loadedImage);
        //Make sure converting went ok too
        if (texture == nullptr)
        {
            logSDLError(std::cout, "CreateTextureFromSurface");
        }
    }
    else
    {
        logSDLError(std::cout, "LoadBMP");
    }
    return texture;
}
```

``` cpp
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
    //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    //Query the texture to get its width and height to use
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, tex, NULL, &dst);
}
```

