#pragma once

#define getChunkBlockX(location) ((uint16_t)(location << 12) >> 12)
#define getChunkBlockY(location) ((uint16_t)(location << 8) >> 12)
#define getChunkBlockZ(location) ((uint16_t)(location << 4) >> 12)