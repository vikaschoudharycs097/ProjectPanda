/*******************************************************
 * Dimension class used to store terminal's dimension
 *
 * @author Vikas Choudhary
 * @date   06/08/2023 
 ******************************************************/
#include "Dimension.h"

Dimension::Dimension(): rows(0), columns(0) {
}

Dimension::Dimension(int rows, int columns): rows(rows), columns(columns) {
}

int Dimension::getRows(void) {
    return rows;
}

int Dimension::getColumns(void) {
    return columns;
}

void Dimension::setRows(int rows) {
    this->rows = rows;
}

void Dimension::setColumns(int columns) {
    this->columns = columns;
}