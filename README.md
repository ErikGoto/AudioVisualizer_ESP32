# AudioVisualizer_ESP32
##Processing
  O **Processing** é usado para captar o áudio do computador, e aplicar uma FFT(fast fourier transform). Assim conseguimos separar as frequências que o áudio possui.
  Nesta primeira versão do projeto as frequencias mais baixas, com os graves, são o gatilho para que a ESP32 acenda a fita de led.
  
##ESP32
  Por meio da comunicação Serial a ESP recebe constantemente informações sobre a presença, ou ausência, de graves em determinado tempo. 

Vídeo de demonstração se encontra [neste link](https://www.youtube.com/watch?v=Zr_HBXlm1V4)
