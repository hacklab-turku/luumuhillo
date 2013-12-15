#ifndef __TYPEDEFS_HPP_
#define __TYPEDEFS_HPP_

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Avoid inclusion bugs by defining dummy classes
class ConfigReader;
class DataStorage;
class Input;
class Toolbox;
class SceneHandler;
class Scene;
class Audio;
class map;


// Typedef manager classes
typedef std::shared_ptr<ConfigReader> ConfigReaderPtr;
typedef std::shared_ptr<DataStorage> DataStoragePtr;
typedef std::shared_ptr<Input> InputPtr;
typedef std::shared_ptr<Toolbox> ToolboxPtr;
typedef std::shared_ptr<SceneHandler> SceneHandlerPtr;
typedef std::shared_ptr<Audio> AudioPtr;

// Typedef content classes
typedef std::shared_ptr<sf::Sprite> SpritePtr;
typedef std::shared_ptr<sf::Texture> TexturePtr;
typedef std::shared_ptr<sf::RenderWindow> RenderWindowPtr;
typedef std::shared_ptr<sf::Sound> SoundPtr;
typedef std::shared_ptr<sf::SoundBuffer> SoundBufferPtr;
typedef std::shared_ptr<Scene> ScenePtr;
typedef std::shared_ptr<sf::View> ViewPtr;
typedef std::shared_ptr<sf::Vector2f> Vector2fPtr;

// Typedef enums
typedef enum
{
    GameState_Loading = 1,
    GameState_NewLoop = 2,
    GameState_Input = 3,
    GameState_Logic = 4,
    GameState_Rendering = 5
} GameState;

#endif
