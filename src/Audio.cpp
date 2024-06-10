/*
 * Audio.cpp
 *
 *  Created on: Oct 26.2018
 *
 *  Version 3.0.11b
 *  Updated on: Jun 04.2024
 *      Author: Wolle (schreibfaul1)
 *
 */
#include "Audio.h"
#include "aac_decoder/aac_decoder.h"
#include "flac_decoder/flac_decoder.h"
#include "mp3_decoder/mp3_decoder.h"
#include "opus_decoder/opus_decoder.h"
#include "vorbis_decoder/vorbis_decoder.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
AudioBuffer::AudioBuffer(size_t maxBlockSize) {
    // if maxBlockSize isn't set use defaultspace (1600 bytes) is enough for aac and mp3 player
    if(maxBlockSize) m_resBuffSizeRAM = maxBlockSize;
    if(maxBlockSize) m_maxBlockSize = maxBlockSize;
}

AudioBuffer::~AudioBuffer() {
    if(m_buffer) free(m_buffer);
    m_buffer = NULL;
}

void AudioBuffer::setBufsize(int ram, int psram) {
    if(ram > -1) // -1 == default / no change
        m_buffSizeRAM = ram;
    if(psram > -1) m_buffSizePSRAM = psram;
}

int32_t AudioBuffer::getBufsize() { return m_buffSize; }

size_t AudioBuffer::init() {
    if(m_buffer) free(m_buffer);
    m_buffer = NULL;
    if(psramInit() && m_buffSizePSRAM > 0) {
        // PSRAM found, AudioBuffer will be allocated in PSRAM
        m_f_psram = true;
        m_buffSize = m_buffSizePSRAM;
        m_buffer = (uint8_t*)ps_calloc(m_buffSize, sizeof(uint8_t));
        m_buffSize = m_buffSizePSRAM - m_resBuffSizePSRAM;
    }
    if(m_buffer == NULL) {
        // PSRAM not found, not configured or not enough available
        m_f_psram = false;
        m_buffer = (uint8_t*)heap_caps_calloc(m_buffSizeRAM, sizeof(uint8_t), MALLOC_CAP_DEFAULT | MALLOC_CAP_INTERNAL);
        m_buffSize = m_buffSizeRAM - m_resBuffSizeRAM;
    }
    if(!m_buffer) return 0;
    m_f_init = true;
    resetBuffer();
    return m_buffSize;
}

void AudioBuffer::changeMaxBlockSize(uint16_t mbs) {
    m_maxBlockSize = mbs;
    re
}

// Constructor: Audio::Audio(bool, uint8_t, uint8_t)
Audio::Audio(bool internalDAC, uint8_t i2s_num, uint8_t i2s_mck) {
    // Commenting out unsupported configuration
    // m_i2s_config.mclk_multiple = I2S_MCLK_MULTIPLE_128;
}

// parsePlaylist_M3U8
const char* Audio::parsePlaylist_M3U8() {
    // ...
    char llasc[20];
    snprintf(llasc, sizeof(llasc), "%lld", xMedSeq);
    // ...
    return nullptr;
}

// m3u8_findMediaSeqInURL
uint64_t Audio::m3u8_findMediaSeqInURL() {
    // ...
    char llasc[20];
    snprintf(llasc, sizeof(llasc), "%lld", b);
    // ...
    return 0;
}

// setPinout
bool Audio::setPinout(uint8_t bclk, uint8_t wclk, uint8_t dout, int8_t mclk) {
    // Commenting out unsupported configuration
    // m_pin_config.mck_io_num = mclk;
    return true;
}

// setI2SCommFMT_LSB
void Audio::setI2SCommFMT_LSB(bool lsb) {
    if (lsb) {
        m_i2s_config.communication_format = I2S_COMM_FORMAT_I2S;
    } else {
        m_i2s_config.communication_format = I2S_COMM_FORMAT_I2S;
    }
}

