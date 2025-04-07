ADR-14: Register Allocator Class for Floating Point Expression Evaluator

Status

Accepted

Context

The floating-point expression evaluator requires efficient register allocation and management to maximize execution performance. The primary challenges include:

Limited Number of XMM Registers: Only 16 XMM registers (xmm0 - xmm15) are available for floating-point operations.

Dynamic Register Allocation: The system must allocate and free registers dynamically based on usage.

Spilling and Reloading: When all registers are in use, the least recently used (LRU) register should be spilled to memory.

Support for General-Purpose (GP) Register Caching: Some values can be stored in GP registers to improve performance.

Thread-Local Memory for Spilling: Spilled registers must be stored in a dedicated memory region to avoid interference between threads.

Decision

To address these challenges, a RegisterTracker class has been implemented to manage XMM and GP registers efficiently. The key features include:

Dynamic Register Allocation: Registers are assigned as needed and tracked via a registerMap.

Free List Management: Available XMM registers are stored in freeXmmRegisters and are allocated on demand.

Register Reuse Optimization: The system reuses registers when possible to minimize spills.

Spill and Reload Mechanism:

Spills occur when no free registers are available.

The spilled variable is stored in a thread-local memory buffer (gSpillSlotMemory).

The register is freed and later reloaded when needed.

LRU-based Eviction: The least recently used register is spilled first to optimize reuse.

GP Register Caching:

If enabled, frequently accessed values are stored in GP registers (r12, r13, r14, r15).

Cached values can be quickly reloaded without accessing main memory.

Assembler Integration: The class interacts with asmjit::x86 to generate assembly instructions for spills and reloads.

Debugging Utilities:

printRegisterStatus() provides an overview of active registers, spilled values, and cached GP values.

Various debug messages are available to track allocation and spill decisions.

Consequences

The implementation of RegisterTracker provides several benefits:

Improved Performance: Efficient register allocation reduces unnecessary spills, leading to faster execution.

Better Memory Management: Spilled values are stored in dedicated thread-local memory, reducing memory overhead.

Enhanced Debugging: The debug utilities allow easy inspection of register states during execution.

Scalability: The design supports multi-threaded execution by ensuring that each thread has its own spill memory buffer.

However, there are some trade-offs:

Increased Complexity: The implementation introduces additional bookkeeping overhead to track register states.

Potential Performance Overhead: If not tuned correctly, excessive spills and reloads may degrade performance.

Future Considerations

Improve Heuristic for Register Eviction: The LRU strategy could be enhanced with additional heuristics (e.g., weighted frequency of access).

Support for Additional Architectures: The system is currently designed for x86-64; extending support for ARM architectures may require further modifications.

Optimize GP Register Caching: The GP register caching strategy can be further refined to prioritize high-use variables.

This decision ensures that the floating-point expression evaluator has a robust and efficient register management system, which is critical for maintaining high performance during expression evaluation.