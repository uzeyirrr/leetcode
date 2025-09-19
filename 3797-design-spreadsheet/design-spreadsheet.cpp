#include <unordered_map>
#include <string>
using namespace std;

class Spreadsheet {
private:
    int rows;
    unordered_map<string, int> cells; // Store non-zero values: cell_reference -> value
    
    // Parse cell reference like "A1" into column index and row
    pair<int, int> parseCell(const string& cell) {
        int col = cell[0] - 'A'; // Convert A-Z to 0-25
        int row = stoi(cell.substr(1)); // Convert row string to int (1-based)
        return {col, row};
    }
    
    // Get the value of a cell (returns 0 if not set)
    int getCellValue(const string& cell) {
        if (cells.find(cell) != cells.end()) {
            return cells[cell];
        }
        return 0;
    }
    
    // Parse an operand which can be either a cell reference or integer
    int parseOperand(const string& operand) {
        // Check if it's a digit (integer)
        bool isNumber = true;
        for (char c : operand) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }
        
        if (isNumber) {
            return stoi(operand);
        } else {
            // It's a cell reference
            return getCellValue(operand);
        }
    }
    
public:
    Spreadsheet(int rows) {
        this->rows = rows;
    }
    
    void setCell(string cell, int value) {
        if (value == 0) {
            // Remove from map if setting to 0
            cells.erase(cell);
        } else {
            cells[cell] = value;
        }
    }
    
    void resetCell(string cell) {
        cells.erase(cell);
    }
    
    int getValue(string formula) {
        // Remove the '=' prefix
        string expression = formula.substr(1);
        
        // Find the '+' operator
        size_t plusPos = expression.find('+');
        string leftOperand = expression.substr(0, plusPos);
        string rightOperand = expression.substr(plusPos + 1);
        
        // Parse each operand (could be cell reference or integer)
        int leftValue = parseOperand(leftOperand);
        int rightValue = parseOperand(rightOperand);
        
        return leftValue + rightValue;
    }
};

/**
 * Your Spreadsheet object will be instantiated and called as such:
 * Spreadsheet* obj = new Spreadsheet(rows);
 * obj->setCell(cell,value);
 * obj->resetCell(cell);
 * int param_3 = obj->getValue(formula);
 */