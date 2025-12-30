#pragma once

#include <cmath>
#include <cstdint>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class GpsProcessor {
   public:
    struct Coords {
        double lat;
        double lon;
        double alt;

        bool isValid() const { return lat != 0.0 || lon != 0.0; }
    };

    /**
     * @param minDistanceMeters Min distance change to trigger a send.
     * @param maxTransmitIntervalMin Min time between movement-based sends (>= 1).
     * @param minSendIntervalMin Force a send after this time even if no movement.
     */
    GpsProcessor(float minDistanceMeters, uint32_t maxTransmitIntervalMin, uint32_t minSendIntervalMin) {
        setMinDistance(minDistanceMeters);
        setMaxTransmitInterval(maxTransmitIntervalMin);
        setMinSendInterval(minSendIntervalMin);

        _lastSentCoords = {0.0, 0.0, 0.0};
        _currentCoords = {0.0, 0.0, 0.0};
        _lastSendTimeMs = 0;
        _hasSentOnce = false;
    }

    void setMinDistance(float meters) { _minDist = meters; }

    void setMaxTransmitInterval(uint32_t minutes) {
        _maxTransmitInt = (minutes < 1) ? 1 : minutes;
    }

    void setMinSendInterval(uint32_t minutes) {
        if (minutes < _maxTransmitInt) minutes = _maxTransmitInt;
        _minSendInt = minutes;
    }

    void updateCoordinates(double lat, double lon, double alt) {
        if (lat != 0.0 || lon != 0.0) {
            _currentCoords = {lat, lon, alt};
        }
    }

    Coords getCurrentCoords() const { return _currentCoords; }

    /**
     * Call this in your main loop.
     * @param currentMillis current system uptime in milliseconds.
     * @return true if conditions are met to send via radio.
     */
    bool loop(uint32_t currentMillis) {
        if (!_currentCoords.isValid()) return false;

        // Force send on the very first valid coordinate received after boot
        if (!_hasSentOnce) {
            markAsSent(currentMillis);
            return true;
        }

        uint32_t elapsedMinutes = (currentMillis - _lastSendTimeMs) / 60000;
        float distance = calculateHorizontalDistance(_lastSentCoords, _currentCoords);

        if (elapsedMinutes >= _minSendInt) {
            markAsSent(currentMillis);
            return true;
        }

        if (distance >= _minDist && elapsedMinutes >= _maxTransmitInt) {
            markAsSent(currentMillis);
            return true;
        }

        return false;
    }

   private:
    Coords _lastSentCoords;
    Coords _currentCoords;
    uint32_t _lastSendTimeMs;

    float _minDist;
    uint32_t _maxTransmitInt;
    uint32_t _minSendInt;
    bool _hasSentOnce;

    void markAsSent(uint32_t currentMillis) {
        _lastSentCoords = _currentCoords;
        _lastSendTimeMs = currentMillis;
        _hasSentOnce = true;
    }

    float calculateHorizontalDistance(Coords c1, Coords c2) {
        double dLat = (c2.lat - c1.lat) * M_PI / 180.0;
        double dLon = (c2.lon - c1.lon) * M_PI / 180.0;

        double lat1 = c1.lat * M_PI / 180.0;
        double lat2 = c2.lat * M_PI / 180.0;

        double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
                   std::sin(dLon / 2) * std::sin(dLon / 2) * std::cos(lat1) * std::cos(lat2);
        double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
        return std::abs(6371000.0 * c);  // Earth radius in meters
    }
};