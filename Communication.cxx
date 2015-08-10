#include "Communication.hxx"

Communication::Communication(const char* requestname, const char* responsename, const char* mapname, std::size_t mapsize, std::ios_base::openmode mapmode) : request(requestname), response(responsename), memorymap(mapname, mapsize, mapmode)
{
    request.create();
    response.create();

    if (memorymap.open())
    {
        memorymap.map();
    }
}

void Communication::ProcessRequests()
{
    if (request.wait(0))
    {
        std::uint32_t* RequestID = static_cast<std::uint32_t*>(memorymap.data());

        switch(*RequestID)
        {
        case kTexture:
            break;

        case kModel:
            break;
        }
    }
}

void Communication::ProcessResponses()
{

}
