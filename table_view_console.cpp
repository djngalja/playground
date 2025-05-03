#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Column {
    std::string header;
    std::size_t width;
};

class Table {
public:
    void add_column(const std::string&);

    template<typename T, typename... Types>
    void add_row(T first, Types... tail) {
        std::ostringstream oss;
        oss << first;
        temp_vec.push_back(oss.str());
        add_row(tail...);
    }

    template<typename... Types>
    void add_row(bool first, Types... tail) {
        if (first) { temp_vec.push_back("+"); }
        else { temp_vec.push_back("-"); }
        add_row(tail...);
    }

    void add_row();

    void print_border() const;
    void print_headers() const;
    void print_rows() const;
private:
    std::vector<Column> columns {};
    std::vector<std::vector<std::string>> rows {};

    const char hor_border_style {'='};
    const char vert_border_style {'|'};
    const char edge_style {'+'};
    const int margin {1}; // margin width in chars

    std::vector<std::string> temp_vec {};
};


int main()  {
    Table tb;

    tb.add_column("Score");
    tb.add_column("Password");
    tb.add_column("Has_id");

    tb.add_row(23, "pswd1234");
    tb.add_row(79, "fdhdg12ghfd4", false);
    tb.add_row(13, "dgfuyegf");
    tb.add_row(7);
    tb.add_row(3366666743775, "hbdgw8r7gt5gcfbaebi", true);
    tb.add_row();

    tb.print_border();
    tb.print_headers();
    tb.print_border();
    tb.print_rows();
    tb.print_border();
    return 0;
}

void Table::add_column(const std::string& header) {
    columns.push_back(Column{header, header.size() + margin * 2});
}

void Table::add_row() {
    // Add empty cells if the given number of cells is less than the number of columns
    if (temp_vec.size() < columns.size()) {
        std::size_t diff = columns.size() - temp_vec.size();
        while (diff--) {
            temp_vec.push_back({});
        }
    }
    // Update column width to fit its widest cell
    for (std::size_t i = 0; i != temp_vec.size(); ++i) {
        if (columns[i].width < temp_vec[i].size() + margin * 2) {
            columns[i].width = temp_vec[i].size() + margin * 2;
        }
    }
    rows.push_back(temp_vec);
    temp_vec.clear();
}

void Table::print_border() const {
    std::string border {edge_style};
    for (const auto& column : columns) {
        border += std::string(column.width, hor_border_style) + edge_style;
    }
    border += '\n';
    std::cout << border;
}

void Table::print_headers() const {
    std::string headers;
    for (const auto& column : columns) {
        int left = (column.width - column.header.size()) / 2;
        int right = column.width - column.header.size() - left;
        headers += vert_border_style + std::string(left, ' ') + column.header + std::string(right, ' ');
    }
    headers += vert_border_style;
    headers += '\n';
    std::cout << headers;
}

void Table::print_rows() const {
    for (const auto& row : rows) {
        std::string row_str;
        for (std::size_t i = 0; i < columns.size(); ++i) {
            int left = (columns[i].width - row[i].size()) / 2;
            int right = columns[i].width - row[i].size() - left;
            row_str += vert_border_style + std::string(left, ' ') + row[i] + std::string(right, ' ');
        }
    row_str += vert_border_style;
    row_str += '\n';
    std::cout << row_str;
    }
}
