#ifndef __TYPEDEFS_HPP_
#define __TYPEDEFS_HPP_

#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include <mutex>

// Avoid inclusion bugs by defining dummy classes
class ConfigReader;
class DataStorage;
class Input;
class Toolbox;
class SceneHandler;
class Scene;
class Audio;
class map;
class NetworkedInput;
class Server;
class ServerSocket;

// Typedef manager classes
typedef std::shared_ptr<ConfigReader> ConfigReaderPtr;
typedef std::shared_ptr<DataStorage> DataStoragePtr;
typedef std::shared_ptr<Input> InputPtr;
typedef std::shared_ptr<Toolbox> ToolboxPtr;
typedef std::shared_ptr<SceneHandler> SceneHandlerPtr;
typedef std::shared_ptr<Audio> AudioPtr;
typedef std::shared_ptr<Server> ServerPtr;
typedef std::shared_ptr<ServerSocket> ServerSocketPtr;
typedef std::shared_ptr<std::thread> ThreadPtr;
typedef std::shared_ptr<std::mutex> MutexPtr;
typedef std::shared_ptr<NetworkedInput> NetworkedInputPtr;

// Typedef content classes
typedef std::shared_ptr<sf::Sprite> SpritePtr;
typedef std::shared_ptr<sf::Texture> TexturePtr;
typedef std::shared_ptr<sf::RenderWindow> RenderWindowPtr;
typedef std::shared_ptr<sf::Sound> SoundPtr;
typedef std::shared_ptr<sf::SoundBuffer> SoundBufferPtr;
typedef std::shared_ptr<Scene> ScenePtr;
typedef std::shared_ptr<sf::View> ViewPtr;
typedef std::shared_ptr<sf::Vector2f> Vector2fPtr;
typedef std::shared_ptr<sf::Socket> SocketPtr;
typedef std::shared_ptr<sf::UdpSocket> UdpSocketPtr;

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
