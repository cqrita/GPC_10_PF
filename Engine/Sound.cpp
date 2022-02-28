#include "Sound.h"
#include <string>
#include <map>
#include <cassert>
#include <d3d11.h>
#include <mmsystem.h>
#include <dsound.h>
#include <cassert>
#include "Resource.h"
#include <iostream>
#if not defined _DEBUG
#define MUST(Expression) (      (         (Expression)))
#else
#define MUST(Expression) (assert(SUCCEEDED(Expression)))
#endif
namespace Engine::Sound
{
	namespace
	{
		IDirectSound8* m_DirectSound = nullptr;
		IDirectSoundBuffer* m_primaryBuffer = nullptr;
	}
	namespace Effect
	{
		namespace 
		{
			struct WaveHeaderType
			{
				char chunkId[4];
				unsigned long chunkSize;
				char format[4];
				char subChunkId[4];
				unsigned long subChunkSize;
				unsigned short audioFormat;
				unsigned short numChannels;
				unsigned long sampleRate;
				unsigned long bytesPerSecond;
				unsigned short blockAlign;
				unsigned short bitsPerSample;
				char dataChunkId[4];
				unsigned long dataSize;
			};
			struct SoundBuffer
			{
				WaveHeaderType waveFileHeader;
				unsigned char* waveData;
			};
			std::map<std::string const, SoundBuffer> Storage;
			void Import(std::string const& file)
			{
				IDirectSoundBuffer8* secondaryBuffer = nullptr;
				FILE* filePtr = nullptr;
				const char* filename = file.c_str();
				fopen_s(&filePtr, filename, "rb");
				

				// Read in the wave file header.
				if (filePtr != nullptr)
				{
					WaveHeaderType waveFileHeader;
					MUST(fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr));


					
					
					

					MUST(fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET));

					// Create a temporary buffer to hold the wave file data.
					unsigned char* waveData = new unsigned char[waveFileHeader.dataSize];


					// Read in the wave file data into the newly created buffer.
					MUST(fread(waveData, 1, waveFileHeader.dataSize, filePtr));


					// Close the file once done reading.
					MUST(fclose(filePtr));


					SoundBuffer soundBuffer = { waveFileHeader ,waveData };
					{
						UINT const top = static_cast<UINT>(file.find_first_of('/') + sizeof(char));
						UINT const bot = static_cast<UINT>(file.find_last_of('.'));

						Storage.try_emplace(file.substr(top, bot - top), soundBuffer);
					}
				}
			}
		}
		void Component::Start()
		{
			if (Name != nullptr)
			{
				SoundBuffer soundBuffer = Storage.at(Name);
				WaveHeaderType waveFileHeader = soundBuffer.waveFileHeader;
				unsigned char* waveData = soundBuffer.waveData;

				// Set the wave format of secondary buffer that this wave file will be loaded onto.
				WAVEFORMATEX waveFormat;
				waveFormat.wFormatTag = waveFileHeader.audioFormat;
				waveFormat.nSamplesPerSec = waveFileHeader.sampleRate;
				waveFormat.wBitsPerSample = waveFileHeader.bitsPerSample;
				waveFormat.nChannels = waveFileHeader.numChannels;
				waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
				waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
				waveFormat.cbSize = 0;

				// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
				DSBUFFERDESC bufferDesc;
				bufferDesc.dwSize = sizeof(DSBUFFERDESC);
				bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
				bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
				bufferDesc.dwReserved = 0;
				bufferDesc.lpwfxFormat = &waveFormat;
				bufferDesc.guid3DAlgorithm = GUID_NULL;


				IDirectSoundBuffer* tempBuffer = nullptr;
				
				MUST(m_DirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL));

				// Test the buffer format against the direct sound 8 interface and create the secondary buffer.

				MUST(tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&m_secondaryBuffer1));
				// Release the temporary buffer.
				tempBuffer->Release();
				tempBuffer = 0;

				// Lock the secondary buffer to write wave data into it.
				unsigned char* bufferPtr = new unsigned char[waveFileHeader.dataSize];
				unsigned long bufferSize = 0;
				MUST((m_secondaryBuffer1)->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0));

				// Copy the wave data into the buffer.
				if (bufferPtr != nullptr)
				{
					memcpy_s(bufferPtr, waveFileHeader.dataSize, waveData, waveFileHeader.dataSize);
				}
				// Unlock the secondary buffer after the data has been written to it.
				MUST((m_secondaryBuffer1)->Unlock((void*)bufferPtr, bufferSize, NULL, 0));
			}			
		}
		void Component::Play()
		{
			MUST(m_secondaryBuffer1->SetCurrentPosition(0));			
			// Set volume of the buffer to 100%.
			MUST(m_secondaryBuffer1->SetVolume(Volume));
			// Play the contents of the secondary sound buffer.
			MUST(m_secondaryBuffer1->Play(0, 0, 0));
		}

		void Component::Music()
		{
			MUST(m_secondaryBuffer1->SetCurrentPosition(0));
			// Set volume of the buffer to 100%.
			MUST(m_secondaryBuffer1->SetVolume(Volume));
			// Play the contents of the secondary sound buffer.
			MUST(m_secondaryBuffer1->Play(0, 0, DSBPLAY_LOOPING));
		}

		void Component::Stop()
		{
			m_secondaryBuffer1->Stop();
		}

		void Component::End()
		{
			if (m_secondaryBuffer1)
			{
				m_secondaryBuffer1->Release();
				m_secondaryBuffer1 = 0;
			}
		}
		
	}
	void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{
		switch (uMessage)
		{
		case WM_CREATE:
		{

			// Initialize the direct sound interface pointer for the default sound device.
			MUST(DirectSoundCreate8(NULL, &m_DirectSound, NULL));
			

			// Set the cooperative level to priority so the format of the primary sound buffer can be modified.
			MUST(m_DirectSound->SetCooperativeLevel(hWindow, DSSCL_PRIORITY));
			

			// Setup the primary buffer description.
			DSBUFFERDESC bufferDesc;
			bufferDesc.dwSize = sizeof(DSBUFFERDESC);
			bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
			bufferDesc.dwBufferBytes = 0;
			bufferDesc.dwReserved = 0;
			bufferDesc.lpwfxFormat = NULL;
			bufferDesc.guid3DAlgorithm = GUID_NULL;

			// Get control of the primary sound buffer on the default sound device.
			MUST(m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL));
			

			// Setup the format of the primary sound bufffer.
			// In this case it is a .WAV file recorded at 44,100 samples per second in 16-bit stereo (cd audio format).
			WAVEFORMATEX waveFormat;
			waveFormat.wFormatTag = WAVE_FORMAT_PCM;
			waveFormat.nSamplesPerSec = 44100;
			waveFormat.wBitsPerSample = 16;
			waveFormat.nChannels = 2;
			waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
			waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
			waveFormat.cbSize = 0;

			// Set the primary buffer to be the wave format specified.
			MUST(m_primaryBuffer->SetFormat(&waveFormat));			
			Resource::Import("Asset/Sound", Effect::Import);
			return;
		}
		
		case WM_DESTROY:
		{
			// Release the primary sound buffer pointer.
			if (m_primaryBuffer)
			{
				m_primaryBuffer->Release();
				m_primaryBuffer = 0;
			}

			// Release the direct sound interface pointer.
			if (m_DirectSound)
			{
				m_DirectSound->Release();
				m_DirectSound = 0;
			}
			return;
		}
		
		}
	}
}