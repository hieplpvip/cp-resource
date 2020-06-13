// To use with console, press Ctrl+Z to send EOF signal

char buffer[1 << 25], *ptr;
void init_in() {
  ptr = buffer;
  buffer[fread(buffer, 1, sizeof(buffer), stdin)] = 0;
}

// positive numbers only
template<typename T>
void readInt(T *x) {
  *x = 0;
  while (*ptr < '0') ++ptr;
  char c;
  while ((c = *ptr++) >= '0')
    *x = (*x) * 10 + c - 48;
}
