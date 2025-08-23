# Performance Report


### Test Configuration
- **CPU**: 6-core processor
- **Test Image**: 3840x2160 pixels
- **Threads**: 6 worker threads
- **Gaussian Kernel**: 25×25 (sigma = 1487,5)


| Operation          | Single-Thread* | Multi-Thread** | Speedup |
|--------------------|----------------|----------------|---------|
| Clockwise          | 231,00 ms      | 49,66 ms       | 4,65x   |
| Counter-clockwise  | 201,00 ms      | 47,33 ms       | 4,24x   |
| Gaussian Filter    | 85297,66 ms    | 19038,33 ms    | 4,48x   |

*Is calculated as an average of three runs of condition stored in the main branch
**Is calculated as an average of three runs of condition stored in current branch
