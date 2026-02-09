# Multi-stage build for smaller image size
FROM gcc:12 AS builder

# Install dependencies (including boost headers that Crow needs)
RUN apt-get update && apt-get install -y \
    cmake \
    make \
    wget \
    libboost-dev \
    && rm -rf /var/lib/apt/lists/*

# Download Crow header-only library
WORKDIR /tmp
RUN wget https://github.com/CrowCpp/Crow/releases/download/v1.0%2B5/crow_all.h

# Set working directory
WORKDIR /app

# Copy source files
COPY CMakeLists.txt .
COPY main.cpp .

# Copy crow header from /tmp
RUN cp /tmp/crow_all.h .

# Build the application
RUN mkdir build && cd build && \
    cmake .. && \
    cmake --build .

# Runtime stage - use debian:bookworm-slim which matches gcc:12 base
FROM debian:bookworm-slim

# Install only runtime dependencies
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

# Create non-root user for security
RUN useradd -m -u 1000 appuser

# Copy binary from builder stage
WORKDIR /app
COPY --from=builder /app/build/microservice .

# Change ownership to non-root user
RUN chown -R appuser:appuser /app

# Switch to non-root user
USER appuser

# Expose port 8080
EXPOSE 8080

# Run the application
CMD ["./microservice"]