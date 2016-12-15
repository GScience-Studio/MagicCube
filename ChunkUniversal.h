#pragma once

#define getChunkBlockX(location) ((uint16_t)(location << 12) >> 12)
#define getChunkBlockY(location) ((uint16_t)(location << 8) >> 12)
#define getChunkBlockZ(location) ((uint16_t)(location << 4) >> 12)

#ifdef _DEBUG
#define blockChunkLocationToShort(x,y,z) \
(((x > 16 || x < 0) || \
(y > 16 || y < 0) || \
(z > 16 || z < 0)) ? 256 : \
x + (y << 4) + (z << 8))
#else
#define blockChunkLocationToShort(x,y,z) (x + (y << 4) + (z << 8))
#endif