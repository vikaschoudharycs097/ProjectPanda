/*******************************************************
 * Dimension class used to store terminal's dimension
 *
 * @author Vikas Choudhary
 * @date   06/08/2023 
 ******************************************************/
#ifndef DIMENSION_H
#define DIMENSION_H

class Dimension {
private:
    int rows;
    int columns;

public:
    Dimension();
    Dimension(int rows, int columns);
    int getRows();
    int getColumns();
    void setRows(int rows);
    void setColumns(int columns);
};

#endif