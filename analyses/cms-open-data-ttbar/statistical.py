import ROOT
import numpy as np
from statistical_interference.agc_sample import AGC_Sample
from statistical_interference.rebinning_tool import RebinningTool
from statistical_interference.extra import MuteTool
from statistical_interference.drawer import Visualization, DrawModel

def fit_histograms(filename = ""):
    print(f"fitting histograms from input file: {filename}")