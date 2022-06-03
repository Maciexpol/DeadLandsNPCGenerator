#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QString>
#include <QtXml\QDomDocument>

/*!
 * \brief Abstract class to help serialize application objects
 */
class Serializable
{
public:
    /*!
     * \brief Serialize element into QDomElement
     * \param doc - any QDomDocument object
     * \return QDomElement - serialized object stored in one single element
     */
    virtual QDomElement XmlSerialize(QDomDocument &doc) const = 0;

    /*!
     * \brief Deserialize QDomElement into object
     * \param element - QDomElement of an object
     */
    virtual void XmlDeserialize(const QDomElement &element) = 0;

    /*!
     * \brief Check whether object values meet criteria to be serialized
     */
     virtual bool XmlValidate() const {return true;};
};

#endif // SERIALIZABLE_H
