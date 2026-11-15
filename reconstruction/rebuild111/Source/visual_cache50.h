/* MIT. Native renderer registers one synchronous release hook after startup.
 * World/class loaders use it only after the GPU has finished queued draws.
 * Portable loader tests do not need to link a GPU implementation.
 */
#ifndef MYRO_VISUAL_CACHE50_H
#define MYRO_VISUAL_CACHE50_H
static void (*visualCacheRelease50)(void);
#endif
