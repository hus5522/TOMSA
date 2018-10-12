{
    "targets": [
        {
            "target_name": "TOA",
            "sources": [ 
                "src/main.cpp",
                "src/Line.cpp",
                "src/Position.cpp",
                "src/ConcavetToConvex.cpp",
                "src/PointInPolygonAlgorithm.cpp",
                "src/TimeOptimizationAlgorithm.cpp" ],
            "include_dirs": [
                "src",
                "header",
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}