function isValid(word: string): boolean {
    if (word.length < 3) {
        return false;
    }

    const validCharRegex = /^[a-zA-Z0-9]+$/;
    if (!validCharRegex.test(word)) {
        return false;
    }

    const vowels = new Set(['a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U']);
    let hasVowel = false;
    let hasConsonant = false;

    for (const char of word) {
        // Check if the character is an English letter (case-insensitive)
        if (/[a-zA-Z]/.test(char)) {
            if (vowels.has(char)) {
                hasVowel = true;
            } else {
                hasConsonant = true;
            }
        }
        
        // Optimization: if both are found, we can stop iterating
        if (hasVowel && hasConsonant) {
            return true;
        }
    }

    return hasVowel && hasConsonant;
}
