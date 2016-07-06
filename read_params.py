#!/usr/bin/python
import os,re,sys
import numpy as np
model_file = open("lstm_model.npz", 'rb')
npz_file = np.load(model_file)

print npz_file.files
print "================= Parameters of the Model. ==============================="
print "Wemb:",npz_file['Wemb']
print "b:",npz_file['b']
print "lstm_b:",npz_file['lstm_b']
print "history_errs:",npz_file['history_errs']
print "U:",npz_file['U']
print "lstm_U:",npz_file['lstm_U']
print "lstm_W:",npz_file['lstm_W']
