#pragma once

namespace MVX
{
  enum CameraState
  {
    OFFLINE = -1,
    STBY,
    GRAPH_LOADING,
    GRAPH_LOADED,
    GRAPH_PLAYING,
    GRAPH_PAUSED,
    GRAPH_STOPPED,
    RECORDING,
    HARVESTING,
    GRAPH_PROCESSING_FAILED
  };

  enum GraphInfoType
  {
    GRAPH_INFO,
    GRAPH_DEBUG,
    GRAPH_ERROR,
  };

  enum CalibrationState
  {
    UNKNOWN_CALIBRATION,
    OUT_OF_CALIBRATION,
    ON_CALIBRATION
  };

}