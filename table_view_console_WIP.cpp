#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct Column {
    std::string header;
    int width;
};

class Table {
    std::vector<Column> columns {};
    int table_width {};
    const char hor_border_style {'-'};
    const char vert_border_style {'|'};
    const char edge_style {'+'};
    std::string border {};
    std::vector<std::vector<std::string>> rows {};
    std::vector<std::string> temp_vec {};
public:
    void add_column(const std::string& header, int width) {
        columns.push_back(Column{header, width});
        if (table_width) { table_width++; };
        table_width += width;
        border = edge_style + std::string(table_width, hor_border_style) + edge_style + '\n';
    }
    template<typename T, typename... Types>
    void add_row(T first, Types... tail) {
        std::ostringstream oss;
        oss << first;
        temp_vec.push_back(oss.str());
        add_row(tail...);
    }
    void add_row() {
        rows.push_back(temp_vec);
        temp_vec.clear();
    }
    void print_border() const {
        std::cout << border;
    }
    void print_headers() const {
        std::string headers;
        for (const auto& column : columns) {
            headers += vert_border_style + std::string(column.width-column.header.size(), ' ') + column.header;
        }
        headers += vert_border_style;
        headers += '\n';
        std::cout << headers;
    }
    void print_rows() const {
        for (const auto& row : rows) {
            std::string row_str;
            for (std::size_t i=0; i<columns.size(); ++i) {
                row_str += vert_border_style + std::string(columns[i].width-row[i].size(), ' ') + row[i];
            }
        row_str += vert_border_style;
        row_str += '\n';
        std::cout << row_str;
        }
    }
};

int main()  {
    Table tb;
    tb.add_column("Score", 10);
    tb.add_column("Password", 25);
    tb.add_row(23, "pswd1234");
    tb.add_row(79, "fdhdg12ghfd4");
    tb.print_border();
    tb.print_headers();
    tb.print_border();
    tb.print_rows();
    tb.print_border();
    return 0;
}
