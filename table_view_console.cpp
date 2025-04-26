#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct Column {
    std::string header;
    std::size_t width;
};

class Table {
    std::vector<Column> columns {};
    int table_width {};
    std::string border {};
    std::vector<std::vector<std::string>> rows {};
    const char hor_border_style {'-'};
    const char vert_border_style {'|'};
    const char edge_style {'+'};
    std::vector<std::string> temp_vec {};
public:
    void add_column(const std::string&, std::size_t);
    template<typename T, typename... Types>
    void add_row(T first, Types... tail) {
        std::ostringstream oss;
        oss << first;
        temp_vec.push_back(oss.str());
        add_row(tail...);
    }
    void add_row();
    void print_border() const;
    void print_headers() const;
    void print_rows();
};


int main()  {
    Table tb;

    tb.add_column("Score", 10);
    tb.add_column("Password", 25);
    tb.add_column("Has_id", 3);

    tb.add_row(23, "pswd1234");
    tb.add_row(79, "fdhdg12ghfd4", false);
    tb.add_row(13, "dgfuyegf");
    tb.add_row(7);
    tb.add_row(3366666743775, "hbdgw8r7gt5gc6tc78gfufbaebi", true);

    tb.print_border();
    tb.print_headers();
    tb.print_border();
    tb.print_rows();
    tb.print_border();
    return 0;
}


void Table::add_column(const std::string& header, std::size_t width) {
    std::size_t final_width = (header.size() > width) ? header.size() : width;
    columns.push_back(Column{header, final_width});
    if (table_width) { table_width++; };
    table_width += final_width;
    border = edge_style + std::string(table_width, hor_border_style) + edge_style + '\n';
}

void Table::add_row() {
    // If the number of cells is less than the number of columns
    if (temp_vec.size() < columns.size()) {
        std::size_t diff = columns.size() - temp_vec.size();
        while (diff--) {
            temp_vec.push_back("");
        }
    }
    rows.push_back(temp_vec);
    temp_vec.clear();
}

void Table::print_border() const {
    std::cout << border;
}

void Table::print_headers() const {
    std::string headers;
    for (const auto& column : columns) {
        headers += vert_border_style + std::string(column.width-column.header.size(), ' ') + column.header;
    }
    headers += vert_border_style;
    headers += '\n';
    std::cout << headers;
}

void Table::print_rows() {
    for (auto& row : rows) {
        std::string row_str;
        for (std::size_t i=0; i<columns.size(); ++i) {
            // If the width of a cell is greater than the width of its column
            if (row[i].size() > columns[i].width) {
                row[i].resize(columns[i].width);
            }
            row_str += vert_border_style + std::string(columns[i].width-row[i].size(), ' ') + row[i];
        }
    row_str += vert_border_style;
    row_str += '\n';
    std::cout << row_str;
    }
}
