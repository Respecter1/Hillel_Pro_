#include <iostream> // std::cout, std::cin, std::cerr
#include <memory> // std::unique_ptr, std::make_unique
#include <string> // std::string
#include <fstream> // std::fstream
#include <limits> // std::numeric_limits

class FileWrapper {
public:
    enum class Mode
    {
        READ,
        WRITE
    };

    // -------------------
    // --- Constructor ---
    // -------------------
    FileWrapper(const std::string& filename, Mode mode = Mode::WRITE)
        : file_read_write_ptr(std::make_unique<std::fstream>()), mode(mode)
    {
        std::ios_base::openmode open_mode = (mode == Mode::READ) ? std::ios::in : std::ios::out | std::ios::app;
        file_read_write_ptr->open(filename, open_mode);

        if (!file_read_write_ptr->is_open())
        {
            std::cerr << "Failed to open file: " << filename << std::endl;
        }
    }

    // Disable copy constructor
    FileWrapper(const FileWrapper& other) = delete;

    // Move constructor
    FileWrapper(FileWrapper&& other) noexcept
    {
        Move(other);
    }

    // ------------------
    // --- Destructor ---
    // ------------------
    ~FileWrapper()
    {
        close();
    }

    // --------------
    // --- Method ---
    // --------------
    bool write(const std::string& data)
    {
        if (!isOpen() || mode == Mode::READ)
        {
            return false;
        }

        *file_read_write_ptr << data;

        // Ïåðåâ³ðêà, ÷è ñòàëàñÿ ïîìèëêà ï³ä ÷àñ çàïèñó
        if (file_read_write_ptr->fail())
        {
            std::cerr << "Failed to write to file." << std::endl;
            return false;
        }

        return true;
    }

    std::string read()
    {
        if (!isOpen() || mode == Mode::WRITE)
        {
            std::cerr << "File is not open or in write mode\n";
            return {};
        }

        std::string content;
        std::string line;

        while (std::getline(*file_read_write_ptr, line))
        {
            content += line + "\n";
        }

        // Ïåðåâ³ðêà íà ê³íåöü ôàéëó òà ïîìèëêè
        if (file_read_write_ptr->eof())
        {
            file_read_write_ptr->clear(); // Î÷èñòèòè ôëàãè ïîìèëîê
        }
        else if (file_read_write_ptr->fail())
        {
            std::cerr << "Error during reading from file.\n";
        }

        return content;
    }

    bool isOpen() const noexcept
    {
        return file_read_write_ptr && file_read_write_ptr->is_open();
    }

    void close()
    {
        if (isOpen())
        {
            file_read_write_ptr->close();
        }
    }
 
    // ----------------
    // --- Operator ---
    // ----------------
    
    explicit operator bool() const
    {
        return isOpen();
    }

    FileWrapper& operator=(const FileWrapper&) = delete;

    FileWrapper& operator=(FileWrapper&& other) noexcept
    {
        if (this != &other)
        {
            close();
            Move(other);
        }
        return *this;
    }

private:
    std::unique_ptr<std::fstream> file_read_write_ptr;
    Mode mode;

    // ----------------------
    // --- private Method ---
    // ----------------------
    void Move(FileWrapper& other) noexcept
    {
        file_read_write_ptr = std::move(other.file_read_write_ptr);
        mode = other.mode;
        other.file_read_write_ptr = nullptr;
    }

  
};

bool getUserConsent()
{
    int key;
    while (true)
    {
        std::cout << "Do you want to see what's in this file?\n\t\t\tyes = 1\tno = 0\n\t\t\tyour answer: ";
        if (std::cin >> key && (key == 0 || key == 1))
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return key == 1;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter 1 for yes or 0 for no.\n";
    }
}

int main()
{
    try
    {

        FileWrapper file("text1.txt", FileWrapper::Mode::WRITE);

        std::cout << "Enter data to write to the file (type 'exit' to quit):\n";
        std::string userInput;
        while (true)
        {
            std::getline(std::cin, userInput);
            if (userInput == "exit") break;
            if (!file.write(userInput + "\n"))
            {
                std::cerr << "Failed to write data to file.\n";
                throw std::runtime_error("Error writing data to file."); // Êèíóòè âèêëþ÷åííÿ ó ðàç³ ïîìèëêè
            }
        }
        file.close();

        if (getUserConsent())
        {

            FileWrapper fileForReading("text1.txt", FileWrapper::Mode::READ);
            std::cout << "\nFile contents:\n";
            std::string content = fileForReading.read();
            if (!content.empty())
            {
                std::cout << content;
            }
            else
            {
                std::cerr << "Failed to read from file or file is empty.\n";
                throw std::runtime_error("Error reading from file."); // Êèíóòè âèêëþ÷åííÿ ó ðàç³ ïîìèëêè
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

