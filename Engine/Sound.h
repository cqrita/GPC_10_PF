#pragma once
#include <dsound.h>
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

namespace Engine::Sound
{
    namespace Effect
    {
        class Component final
        {
        public:
            void Start();
            void Play();
            void Music();
            void Stop();
            void End();
        public:
            char const* Name = nullptr;
            int Volume = DSBVOLUME_MAX;
        private:
            IDirectSoundBuffer* m_secondaryBuffer1=nullptr;
        };
    }
}