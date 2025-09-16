function debounce(fn, t) {
  let timer;

  return function(...args) {
    // Önceki timer varsa iptal et
    if (timer) clearTimeout(timer);

    // Yeni timer başlat
    timer = setTimeout(() => {
      fn(...args);
    }, t);
  };
}
