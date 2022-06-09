/*
 * File:   collision.cpp
 * Author: Nick (original version), ahnonay (SFML2 compatibility)
 */
#include <SFML/Graphics.hpp>
#include <map>
#include "CollisionDetection.h"

namespace Collision
{
    class BitmaskManager
    {
    public:
        ~BitmaskManager() {
            std::map<const sf::Texture*, sf::Uint8*>::const_iterator end = Bitmasks.end();
            for (std::map<const sf::Texture*, sf::Uint8*>::const_iterator iter = Bitmasks.begin(); iter!=end; iter++)
                delete [] iter->second;
        }
        
        sf::Uint8 GetPixel (const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y) {
                    if (x>tex->getSize().x||y>tex->getSize().y)
                        return 0;

                    // std::cout << "X Should return always true: " << std::to_string() << std::endl;
                    // std::cout << "Y Should return always true: " << std::to_string() << std::endl;
//                    std::cout << "X: " << x << std::endl;
//                    std::cout << "Y: " << y << std::endl;
//                    std::cout << "Mask[" << x+y*tex->getSize().x << "] pixel value: " << int(mask[x+y*tex->getSize().x]) << std::endl;
                    sf::Uint8 pixelValue = mask[x+y*tex->getSize().x];
                    return pixelValue <= 1? (x < tex->getSize().x && y < tex->getSize().y) : pixelValue;
                }
        
        sf::Uint8* GetMask (const sf::Texture* tex) {
            sf::Uint8* mask;
            std::map<const sf::Texture*, sf::Uint8*>::iterator pair = Bitmasks.find(tex);
            if (pair==Bitmasks.end())
            {
                sf::Image img = tex->copyToImage();
                mask = CreateMask (tex, img);
            }
            else
                mask = pair->second;
            
            return mask;
        }
        
        sf::Uint8* CreateMask (const sf::Texture* tex, const sf::Image& img) {
            sf::Uint8* mask = new sf::Uint8[tex->getSize().y*tex->getSize().x];
            
            for (unsigned int y = 0; y<tex->getSize().y; y++)
            {
                for (unsigned int x = 0; x<tex->getSize().x; x++)
                    mask[x+y*tex->getSize().x] = img.getPixel(x,y).a;
            }
            
            Bitmasks.insert(std::pair<const sf::Texture*, sf::Uint8*>(tex,mask));
            
            return mask;
        }
    private:
        std::map<const sf::Texture*, sf::Uint8*> Bitmasks;
    };
    
    BitmaskManager Bitmasks;
    
    bool PixelPerfectTest(const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit) {
        sf::FloatRect Intersection;
        if (Object1.getGlobalBounds().intersects(Object2.getGlobalBounds(), Intersection)) {
            sf::IntRect O1SubRect = Object1.getTextureRect();
            sf::IntRect O2SubRect = Object2.getTextureRect();
            
            sf::Uint8* mask1 = Bitmasks.GetMask(Object1.getTexture());
            sf::Uint8* mask2 = Bitmasks.GetMask(Object2.getTexture());
            
            // Loop through our pixels
            for (int i = Intersection.left; i < Intersection.left+Intersection.width; i++) {
                for (int j = Intersection.top; j < Intersection.top+Intersection.height; j++) {
                    
                    sf::Vector2f o1v = Object1.getInverseTransform().transformPoint(i, j);
                    sf::Vector2f o2v = Object2.getInverseTransform().transformPoint(i, j);
                    
                    // Make sure pixels fall within the sprite's subrect
                    if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
                        o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
                        o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {
                        
                        if (Bitmasks.GetPixel(mask1, Object1.getTexture(), (int)(o1v.x)+O1SubRect.left, (int)(o1v.y)+O1SubRect.top) > AlphaLimit &&
                            Bitmasks.GetPixel(mask2, Object2.getTexture(), (int)(o2v.x)+O2SubRect.left, (int)(o2v.y)+O2SubRect.top) > AlphaLimit)
                            return true;
                        
                    }
                }
            }
        }
        return false;
    }

    bool pixelCollideVector(const sf::Sprite* sprite, sf::Uint8* spriteMask, int blockSize, sf::Vector2f& position, float alphaLimit) {

           // std::cout << "Sprite Left: " << sprite->getGlobalBounds().left << std::endl;
           // std::cout << "Sprite Top: " << sprite->getGlobalBounds().top << std::endl;
           // std::cout << "Sprite Width: " << sprite->getGlobalBounds().width << std::endl;
           // std::cout << "Sprite Height: " << sprite->getGlobalBounds().height << std::endl;
           // std::cout << "Vector X: " << position.x << std::endl;
           // std::cout << "Vector Y: " << position.y << std::endl;
           // std::cout << "Vector Aligned X: " << position.x * blockSize << std::endl;
           // std::cout << "Vector Aligned Y: " << position.y * blockSize << std::endl;

           if(!sprite->getGlobalBounds().contains(position.x * blockSize, (position.y * blockSize)))
               return false;
           sf::IntRect spriteRect = sprite->getTextureRect();

           sf::Vector2f sv = sprite->getTransform().transformPoint(position.x*blockSize, (position.y*blockSize)-2);
           if (int(sv.x) >= 0 && int(sv.y) >= 0 && int(sv.x) < spriteRect.width && int(sv.y) < spriteRect.height) {
                   float pixel = (float) Bitmasks.GetPixel(spriteMask, sprite->getTexture(), (int) (sv.x)+(spriteRect.left), (int)(sv.y)+(spriteRect.top));
                   float pixelAlpha = (float) pixel/255;
                   return pixelAlpha > alphaLimit;
               // return true;
           }
           return false;
       }

    bool pixelCollideTest(const sf::RectangleShape shape, const sf::Sprite* sprite, sf::Uint8 AlphaLimit) {
        sf::FloatRect Intersection;
        if (shape.getGlobalBounds().intersects(sprite->getGlobalBounds(), Intersection)) {
            sf::IntRect O1SubRect = shape.getTextureRect();
            sf::IntRect O2SubRect = sprite->getTextureRect();
            
            sf::Uint8* mask1 = Bitmasks.GetMask(shape.getTexture());
            sf::Uint8* mask2 = Bitmasks.GetMask(sprite->getTexture());
            
            // Loop through our pixels
            for (int i = Intersection.left; i < Intersection.left+Intersection.width; i++) {
                for (int j = Intersection.top; j < Intersection.top+Intersection.height; j++) {
                    
                    sf::Vector2f o1v = shape.getInverseTransform().transformPoint(i, j);
                    sf::Vector2f o2v = sprite->getInverseTransform().transformPoint(i, j);
                    
                    // Make sure pixels fall within the sprite's subrect
                    if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 && 
                        o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
                        o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {
                        
                        if (Bitmasks.GetPixel(mask1, shape.getTexture(), (int)(o1v.x)+O1SubRect.left, (int)(o1v.y)+O1SubRect.top) > AlphaLimit &&
                            Bitmasks.GetPixel(mask2, sprite->getTexture(), (int)(o2v.x)+O2SubRect.left, (int)(o2v.y)+O2SubRect.top) > AlphaLimit)
                            return true;
                        
                    }
                }
            }
        }
        return false;
    }
    
    sf::Uint8* createTextureAndBitmask(const sf::Texture* LoadInto, const std::string& Filename)
       {
           sf::Texture loaded = *LoadInto;
           sf::Image img;

           if (!img.loadFromFile(Filename))
               return 0;
           if (!loaded.loadFromImage(img))
               return 0;
           return Bitmasks.GetMask(&loaded);
           // return true;
       }
    
    sf::Vector2f GetSpriteCenter (const sf::Sprite& Object)
    {
        sf::FloatRect AABB = Object.getGlobalBounds();
        return sf::Vector2f (AABB.left+AABB.width/2.f, AABB.top+AABB.height/2.f);
    }
    
    sf::Vector2f GetSpriteSize (const sf::Sprite& Object)
    {
        sf::IntRect OriginalSize = Object.getTextureRect();
        sf::Vector2f Scale = Object.getScale();
        return sf::Vector2f (OriginalSize.width*Scale.x, OriginalSize.height*Scale.y);
    }
    
    bool CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2) {
        sf::Vector2f Obj1Size = GetSpriteSize(Object1);
        sf::Vector2f Obj2Size = GetSpriteSize(Object2);
        float Radius1 = (Obj1Size.x + Obj1Size.y) / 4;
        float Radius2 = (Obj2Size.x + Obj2Size.y) / 4;
        
        sf::Vector2f Distance = GetSpriteCenter(Object1)-GetSpriteCenter(Object2);
        
        return (Distance.x * Distance.x + Distance.y * Distance.y <= (Radius1 + Radius2) * (Radius1 + Radius2));
    }
    
    class OrientedBoundingBox // Used in the BoundingBoxTest
    {
    public:
        OrientedBoundingBox (const sf::Sprite& Object) // Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
        {
            sf::Transform trans = Object.getTransform();
            sf::IntRect local = Object.getTextureRect();
            Points[0] = trans.transformPoint(0.f, 0.f);
            Points[1] = trans.transformPoint(local.width, 0.f);
            Points[2] = trans.transformPoint(local.width, local.height);
            Points[3] = trans.transformPoint(0.f, local.height);
        }
        
        sf::Vector2f Points[4];
        
        void ProjectOntoAxis (const sf::Vector2f& Axis, float& Min, float& Max) // Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
        {
            Min = (Points[0].x*Axis.x+Points[0].y*Axis.y);
            Max = Min;
            for (int j = 1; j<4; j++)
            {
                float Projection = (Points[j].x*Axis.x+Points[j].y*Axis.y);
                
                if (Projection<Min)
                    Min=Projection;
                if (Projection>Max)
                    Max=Projection;
            }
        }
    };
    
    bool BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2) {
        OrientedBoundingBox OBB1 (Object1);
        OrientedBoundingBox OBB2 (Object2);
        
        // Create the four distinct axes that are perpendicular to the edges of the two rectangles
        sf::Vector2f Axes[4] = {
            sf::Vector2f (OBB1.Points[1].x-OBB1.Points[0].x,
                          OBB1.Points[1].y-OBB1.Points[0].y),
            sf::Vector2f (OBB1.Points[1].x-OBB1.Points[2].x,
                          OBB1.Points[1].y-OBB1.Points[2].y),
            sf::Vector2f (OBB2.Points[0].x-OBB2.Points[3].x,
                          OBB2.Points[0].y-OBB2.Points[3].y),
            sf::Vector2f (OBB2.Points[0].x-OBB2.Points[1].x,
                          OBB2.Points[0].y-OBB2.Points[1].y)
        };
        
        for (int i = 0; i<4; i++)
        {
            float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;
            
            OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
            OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);
            
            if (!((MinOBB2<=MaxOBB1)&&(MaxOBB2>=MinOBB1)))
                return false;
        }
        return true;
    }
}
