#include <string>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // Fonksiyon adı, test ortamındaki beklenen isim olan 'answerString' olarak bırakılmıştır.
    string answerString(string word, int numFriends) {
        int L = word.length();
        int K = numFriends;

        // 1. Köşe Durumu: numFriends = 1
        // Tek bir arkadaş varsa, kelimenin tamamı tek parça olarak kutuya konur.
        // Bu, önceki çözümünüzün başarısız olduğu durumu düzeltir.
        if (K == 1) {
            return word;
        }

        // 2. Genel Durum (K > 1)
        // Bir substringin geçerli bir parçası olabilmesi için, kalan K-1 arkadaş 
        // için en az K-1 karakter (her biri için 1) bırakılması gerekir.
        // Bu nedenle, herhangi bir substringin alabileceği maksimum uzunluk şudur:
        // Max Uzunluk = (Toplam Uzunluk L) - (Kalan K-1 parça için ayrılan min. karakter sayısı)
        int max_len = L - (K - 1);
        
        // Aslında max_len >= 1 olmalıdır. Kısıtlar nedeniyle K <= L olduğundan bu her zaman geçerlidir.
        if (max_len <= 0) {
            // Bu durum, Kısıtlar (1 <= numFriends <= word.length) gereği oluşmamalıdır, 
            // ancak sağlamlık için eklenebilir.
            return ""; 
        }

        // Lexicografik olarak en büyük dizeyi tutar.
        string max_str = "";

        // Her olası başlangıç konumu 'i' için deneriz.
        for (int i = 0; i < L; ++i) {
            
            // Mevcut başlangıç konumu 'i' için, stringin sonuna kadar kaç karakter kalmış?
            int remaining_len = L - i;

            // Bu noktadan başlayarak alabileceğimiz gerçek uzunluk,
            // genel maksimum uzunluk (max_len) ile mevcut kalan uzunluğun minimumudur.
            int current_len = min(max_len, remaining_len); 

            // Eğer alınabilecek uzunluk 0 veya daha az ise, devam etmenin anlamı yok.
            if (current_len <= 0) {
                break;
            }

            // 'i' noktasından başlayan, izin verilen maksimum uzunluktaki substringi al.
            string current_str = word.substr(i, current_len);

            // Lexicografik olarak karşılaştır ve en büyük olanı güncelle.
            // Bir substringin en büyük olması için, o noktadan alınabilecek 
            // en uzun olana bakmak yeterlidir, çünkü daha kısa bir önek her zaman 
            // kendisinden daha uzun olan ana stringten daha küçüktür.
            if (current_str > max_str) {
                max_str = current_str;
            }
        }

        return max_str;
    }
};