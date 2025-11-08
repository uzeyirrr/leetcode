/**
 * @param {string} s
 * @return {number}
 */
const myAtoi = (s) => {
    // Define the 32-bit integer limits
    const INT_MAX = 2147483647; // 2^31 - 1
    const INT_MIN = -2147483648; // -2^31

    let i = 0; // Current index in the string
    const n = s.length;

    // --- 1. Whitespace: Ignore any leading whitespace (" ") ---
    while (i < n && s[i] === ' ') {
        i++;
    }

    // Check if we reached the end after skipping whitespace
    if (i === n) {
        return 0;
    }

    // --- 2. Signedness: Determine the sign ---
    let sign = 1; // Assume positive by default

    if (s[i] === '-') {
        sign = -1;
        i++;
    } else if (s[i] === '+') {
        i++;
    }

    // --- 3. Conversion: Read the integer and handle overflow check simultaneously ---
    let result = 0;

    while (i < n) {
        const char = s[i];
        const digit = char.charCodeAt(0) - '0'.charCodeAt(0);

        // Check if the character is a digit
        if (digit < 0 || digit > 9) {
            break; // Stop reading upon encountering a non-digit character
        }

        // Check for potential overflow BEFORE the multiplication and addition.
        // The check depends on the sign, as the limit magnitude is slightly larger for negative numbers.

        if (sign === 1) {
            // Positive sign: Check against INT_MAX (2147483647)
            // If result > INT_MAX / 10 (214748364) OR
            // If result === INT_MAX / 10 and digit > INT_MAX % 10 (7)
            if (result > Math.floor(INT_MAX / 10) || (result === Math.floor(INT_MAX / 10) && digit > (INT_MAX % 10))) {
                return INT_MAX; // Overflow for positive number
            }
        } else { // sign === -1
            // Negative sign: Check against INT_MIN (-2147483648). We work with positive 'result'
            // The magnitude of INT_MIN is 2147483648.
            // If result > |INT_MIN / 10| (214748364) OR
            // If result === |INT_MIN / 10| and digit > |INT_MIN % 10| (8)
            // Note: INT_MIN / 10 in JS is -214748364.8, Math.floor is -214748365. We use Math.floor(INT_MAX / 10) for the common base magnitude.
            // The max magnitude check is on the positive side: 2147483648.
            const MAX_NEG_MAGNITUDE_DIV10 = 214748364; // Math.floor(2147483648 / 10)
            const MAX_NEG_LAST_DIGIT = 8; // 2147483648 % 10

            if (result > MAX_NEG_MAGNITUDE_DIV10 || (result === MAX_NEG_MAGNITUDE_DIV10 && digit > MAX_NEG_LAST_DIGIT)) {
                return INT_MIN; // Overflow for negative number
            }
        }

        // Safe to update the result (magnitude)
        result = result * 10 + digit;
        i++;
    }

    // --- 4. Rounding: The overflow check is done during conversion (Step 3).
    // The final result is calculated and returned, which is within the range due to Step 3.
    return sign * result;
};