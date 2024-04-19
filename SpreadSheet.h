    #ifndef SPREADSHEET_H
    #define SPREADSHEET_H
    
    class cell;
    class SpreadSheet;


    std::ostream& operator<<(std::ostream& os, const cell& data);
    std::ostream& operator<<(std::ostream& os, const SpreadSheet& data);
    std::istream& operator>>(std::istream& in, cell& ob); 

    class cell{

        public:
    
        friend std::ostream& operator<<(std::ostream& os, const cell& data);
        friend std::istream& operator>>(std::istream& in, cell& ob);
        cell();
        cell(int val);
        cell(std::string val);
        cell(double val);
        cell(const cell& rhv);
        cell(cell&& rhv);

        cell& operator=(int val);
        cell& operator=(double val);
        cell& operator=(std::string val);
        cell& operator=(const cell& rhv);
        cell& operator=(cell&& rhv);  
        cell& operator=(char rhv);  
        cell& operator=(bool rhv);  
        cell& operator=(const std::vector<int>& rhv);



        bool operator==(const cell& rhv);
        bool operator!=(const cell& rhv);


        operator int() const;
        operator std::string() const;
        operator double() const;
        operator std::vector<int>();  



        private:
            std::string val;

    };



     class SpreadSheet{

    friend std::ostream& operator<<(std::ostream& os, const SpreadSheet& data);

        public:

            SpreadSheet();
            SpreadSheet(std::size_t size);
            SpreadSheet(std::size_t row, std::size_t col);
            SpreadSheet(const SpreadSheet& rhv);
            SpreadSheet(SpreadSheet&& rhv);
            ~SpreadSheet();

            class ProxyRow{
                public:
                    ProxyRow(cell* row);
                    cell& operator[](std::size_t colindex);


                private:
                    cell* row;

            };


             ProxyRow operator[](std::size_t rowindex);
            
            void resizeRow(std::size_t rows_size);
            void resizeCol(std::size_t cols_size);
            void resize(std::size_t rows_size, std::size_t cols_size);

            std::size_t row() const;
            std::size_t col() const;


            bool operator==(const SpreadSheet& rhv);
            bool operator!=(const SpreadSheet& rhv);

            void rotate(int reps);
            void mirrorh();
            void mirrorv();
            void mirrorD();
            void mirrord();
            
            void removeRow(int index);
            void removeCol(int index);

            SpreadSheet& slice(std::initializer_list<std::size_t> rows,std::initializer_list<std::size_t> cols);


        private:

            cell** Sheet;
            std::size_t rows;
            std::size_t cols;
            
    };




    #endif