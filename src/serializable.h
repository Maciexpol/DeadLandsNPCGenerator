#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QString>
#include <QtXml\QDomDocument>

/*!
 * \brief Abstract class to help serialize objects into Xml format
 *
 * Provides standardized way of serializing and deserializing objects into Xml format, helping in the process
 * of saving things to files.
 * Any class inheriting from Serializable must implement its own XmlSerialize and XmlDeserialize functions.
 */
class Serializable
{
public:
    /*!
     * \brief Implements process of objects serialization
     *
     * \paragraph example Example serialization:
     * \code{.cpp}
            QDomElement Attribute::XmlSerialize() const {
                QDomElement element;
                element.setTagName("attribute");

                element.setAttribute("name", this->name);
                element.appendChild(dice.XmlSerialize());
                element.appendChild(abilities.XmlSerialize());
                return element;
            }
     * \endcode
     *
     * \return Serialized object
     */
    virtual QDomElement XmlSerialize() const = 0;

    /*!
     * \brief Implements process of objects deserialization
     * \param element Object containing information to deserialize
     *
     * \paragraph example Example deserialization:
     * \code{.cpp}
            void Session::XmlDeserialize(const QDomElement &element){
                this->name = element.attribute("name", "-");
                this->description = element.attribute("description", "-");
                this->creationDate = QDate::fromString(element.attribute("creationDate", ""));
                this->npcCount = static_cast<qint16>(element.attribute("npcCount", "0").toInt());
            }
     * \endcode
     */
    virtual void XmlDeserialize(const QDomElement &element) = 0;

    /*!
     * \brief Check whether object attributes meet criteria to be serialized
     *
     * \return True if object meets given criteria, false otherwise
     */
     virtual bool XmlValidate() const {return true;};
};

#endif // SERIALIZABLE_H
